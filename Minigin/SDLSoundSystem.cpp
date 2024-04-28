#include "SDLSoundSystem.h"

#include <iostream>
//#include <SDL_mixer.h>

//void dae::SDLSoundSystem::Play(const soundId id, const float volume)
//{
//    // Load sound
//    //std::cout << "start to play sound !\n";
//
//    /*if (id >= m_AudioClips.size()) return;
//    Mix_Chunk* sound = m_AudioClips[id];
//    if (sound != nullptr) 
//    {
//        m_Thread = std::jthread{ &SDLSoundSystem::PlaySoundOnThread, this, sound, volume };
//    }
//    else 
//    {
//        std::cerr << "Failed to play sound for ID: " << id << "\n";
//    }*/
//    //std::cout << "Sound played !\n";
//}

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

void dae::SDLSoundSystem::LoadSound(const std::string& path)
{
    //Load all the clips
    //m_Thread = std::jthread(&SDLSoundSystem::LoadOnThread, this, "../Data/qbert/Sounds/QBert Jump.wav");
    m_Thread = std::jthread(&SDLSoundSystem::LoadOnThread, this, path);
}

void dae::SDLSoundSystem::Update()
{
    if (GetPendingEvents().empty()) return;

    if (GetPendingEvents().front().id >= m_AudioClips.size()) return;
    Mix_Chunk* sound = m_AudioClips[GetPendingEvents().front().id];
    if (sound != nullptr)
    {
        m_Thread = std::jthread{ &SDLSoundSystem::PlaySoundOnThread, this, sound, GetPendingEvents().front().volume};
    }
    else
    {
        std::cerr << "Failed to play sound for ID: " << GetPendingEvents().front().id << "\n";
    }
    GetPendingEvents().pop_front();
}

void dae::SDLSoundSystem::PlaySoundOnThread(Mix_Chunk* sound, const float volume)
{
    std::lock_guard soundLock{m_SoundMutex};
    // Adjust volume
    Mix_VolumeChunk(sound, static_cast<int>(volume * MIX_MAX_VOLUME));

    // Play the sound
    Mix_PlayChannel(-1, sound, 0);
}

void dae::SDLSoundSystem::LoadOnThread(const std::string& path)
{
    std::lock_guard loadLock{m_SoundMutex};
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        printf("Unable to load sound: %s\n", Mix_GetError());
    }
    else
    {
        m_AudioClips.emplace_back(sound);
    }
}
