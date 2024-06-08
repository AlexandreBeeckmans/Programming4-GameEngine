#include "SDLSoundSystem.h"

#include <iostream>
#include <SDL_mixer.h>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include <condition_variable>

struct DeleteSound
{
    void operator()(Mix_Chunk* pSound) { Mix_FreeChunk(pSound); }
};

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:

    SDLSoundSystemImpl()
    {
        m_Thread = std::jthread{ &SDLSoundSystemImpl::PlaySoundOnThread, this };
    }
    ~SDLSoundSystemImpl()
    {
        m_IsActive = false;
        m_ConditionalVariable.notify_all();
    }

    void DoPlaySound(const soundId id, const float volume);
    void DoLoadSound(const std::string& path, const soundId id);
    void DoUpdate();
    void DoStopAll();
private:

    void PlaySoundOnThread();
	void LoadOnThread(const std::string& path, const soundId id);
    std::deque<PlayMessageEvent>& GetPendingEvents() { return m_PendingEvents; }

    std::deque<PlayMessageEvent> m_PendingEvents;

    std::unordered_map<int,std::unique_ptr<Mix_Chunk, DeleteSound>> m_AudioClips;

    std::jthread m_Thread;
    std::jthread m_LoadSoundThread;

    std::mutex m_SoundMutex;
    std::condition_variable m_ConditionalVariable{};

    bool m_IsActive{ true };

   
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
    m_ConditionalVariable.notify_all();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoLoadSound(const std::string& path, const soundId id)
{
    LoadOnThread(path, id);
}

void dae::SDLSoundSystem::Update()
{
    m_pImpl->DoUpdate();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoUpdate()
{
    /*if (GetPendingEvents().empty()) return;

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
    GetPendingEvents().pop_front();*/
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::DoStopAll()
{
    std::lock_guard soundLock(m_SoundMutex);
    Mix_HaltChannel(-1); 
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::PlaySoundOnThread()
{


    while(m_IsActive)
    {
        std::unique_lock soundLock{ m_SoundMutex };
        m_ConditionalVariable.wait(soundLock, [&]
        {
                return !GetPendingEvents().empty() || !m_IsActive;
        });

        if (!m_IsActive) return;

        Mix_Chunk* sound = m_AudioClips[GetPendingEvents().front().id].get();
        if (sound != nullptr)
        {

            // Adjust volume
            Mix_VolumeChunk(sound, static_cast<int>(GetPendingEvents().front().volume * MIX_MAX_VOLUME));

            // Play the sound
            Mix_PlayChannel(-1, sound, 0);

        }
        else
        {
            std::cerr << "Failed to play sound for ID: " << GetPendingEvents().front().id << "\n";
        }
        GetPendingEvents().pop_front();
    }
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::LoadOnThread(const std::string& path, const soundId id)
{
    std::lock_guard loadLock{m_SoundMutex};
    std::unique_ptr<Mix_Chunk, DeleteSound> sound = std::unique_ptr<Mix_Chunk, DeleteSound>(Mix_LoadWAV(path.c_str()));
    if (sound == NULL)
    {
        printf("Unable to load sound: %s\n", Mix_GetError());
    }
    else
    {
        m_AudioClips[id] = std::move(sound);
    }
}
