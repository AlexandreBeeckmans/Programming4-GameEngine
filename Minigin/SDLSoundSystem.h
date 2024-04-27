#pragma once
#include <mutex>
#include <SDL_mixer.h>
#include <thread>
#include <vector>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		virtual ~SDLSoundSystem() override = default;
		void Play(const soundId id, const float volume) override;
		virtual void Init() override;
		virtual void LoadSound(const std::string& path) override;

	private:
		void PlaySoundOnThread(Mix_Chunk* sound, const float volume);
		void LoadOnThread(const std::string& path);

		std::vector<Mix_Chunk*> m_AudioClips;
		std::jthread m_Thread;
		std::mutex m_SoundMutex;
	};
}


