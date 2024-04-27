#include "SDLSoundSystem.h"

#include <iostream>
//#include <SDL_mixer.h>

void dae::SDLSoundSystem::Play(const soundId id, const float volume)
{
    // Load sound
    std::cout << "start to play sound !" << std::endl;
    Mix_Chunk* sound = m_AudioClips[id];
    if (sound != nullptr) 
    {
        // Adjust volume
        Mix_VolumeChunk(sound, static_cast<int>(volume * MIX_MAX_VOLUME));

        // Play the sound
        Mix_PlayChannel(-1, sound, 0); // -1 for any available channel, 0 for no loop
    }
    else 
    {
        std::cerr << "Failed to play sound for ID: " << id << std::endl;
    }
    std::cout << "Sound played !" << std::endl;
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

    //Load all the clips
    std::cout << "Load a sound..." << std::endl;
    Mix_Chunk* sound = Mix_LoadWAV("../Data/qbert/Sounds/QBert Jump.wav");
    if (sound == NULL) 
    {
        printf("Unable to load sound: %s\n", Mix_GetError());
    }
    else
    {
        m_AudioClips.emplace_back(sound);
    }
    
}
