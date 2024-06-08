#include "SDLSoundSystem.h"

#include <iostream>
#include <SDL_mixer.h>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:

    SDLSoundSystemImpl() = default;
    ~SDLSoundSystemImpl() = default;
    void DoPlaySound(const soundId id, const float volume);
    void DoLoadSound(const std::string& path, const soundId id);
    void DoUpdate();
    void DoStopAll();
private:

    void PlaySoundOnThread(Mix_Chunk* sound, const float volume);
	void LoadOnThread(const std::string& path, const soundId id);
    std::deque<PlayMessageEvent>& GetPendingEvents() { return m_PendingEvents; }

    std::deque<PlayMessageEvent> m_PendingEvents;

    std::unordered_map<int,Mix_Chunk*> m_AudioClips;
    std::jthread m_Thread;
    std::mutex m_SoundMutex;
};


dae::SDLSoundSystem::SDLSoundSystem()
{
    m_pImpl = new SDLSoundSystemImpl{};
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

void dae::SDLSoundSystem::Play(const soundId id, const float volume)
{
    m_pImpl->DoPlaySound(id, volume);
}

void dae::SDLSoundSystem::StopAll()
{
    m_pImpl->DoStopAll();
}

void dae::SDLSoundSystem::Init()
{
    // Initialize SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Open the audio device
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not open audio! SDL_mixer Error: %s\n", Mix_GetError());
    }


}

void dae::SDLSoundSystem::LoadSound(const std::string& path, const soundId id)
{
    m_pImpl->DoLoadSound(path, id);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoPlaySound(const soundId id, const float volume)
{
    for (PlayMessageEvent& event : m_PendingEvents)
    {
        //if similar sound is already waiting to be played
        if (event.id == id)
        {
            // Use the larger of the two volumes.
            event.volume = std::max(volume, event.volume);

            // Don't need to enqueue.
            return;
        }
    }
    m_PendingEvents.push_back({ id, volume });
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoLoadSound(const std::string& path, const soundId id)
{
    if(m_Thread.joinable())
    {
        m_Thread.join();
    }
	m_Thread = std::jthread(&SDLSoundSystemImpl::LoadOnThread, this, path, id);
    
}

void dae::SDLSoundSystem::Update()
{
    m_pImpl->DoUpdate();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoUpdate()
{
    if (GetPendingEvents().empty()) return;

    if (GetPendingEvents().front().id >= m_AudioClips.size()) return;
    Mix_Chunk* sound = m_AudioClips[GetPendingEvents().front().id];
    if (sound != nullptr)
    {
        if(m_Thread.joinable())
        {
            m_Thread.join();
        }
    	m_Thread = std::jthread{ &SDLSoundSystemImpl::PlaySoundOnThread, this, sound, GetPendingEvents().front().volume };
        
    }
    else
    {
        std::cerr << "Failed to play sound for ID: " << GetPendingEvents().front().id << "\n";
    }
    GetPendingEvents().pop_front();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoStopAll()
{
    std::lock_guard soundLock(m_SoundMutex);
    Mix_HaltChannel(-1); 
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PlaySoundOnThread(Mix_Chunk* sound, const float volume)
{
    std::lock_guard soundLock{m_SoundMutex};

    // Adjust volume
    Mix_VolumeChunk(sound, static_cast<int>(volume * MIX_MAX_VOLUME));

    // Play the sound
    Mix_PlayChannel(-1, sound, 0);
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::LoadOnThread(const std::string& path, const soundId id)
{
    std::lock_guard loadLock{m_SoundMutex};
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        printf("Unable to load sound: %s\n", Mix_GetError());
    }
    else
    {
        m_AudioClips[id] = sound;
    }
}
