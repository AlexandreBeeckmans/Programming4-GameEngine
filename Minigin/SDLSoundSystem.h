#pragma once

#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;
		//void Play(const soundId id, const float volume) override;
		virtual void Init() override;
		virtual void LoadSound(const std::string& path) override;
		virtual void Update() override;

	private:
		/*void PlaySoundOnThread(Mix_Chunk* sound, const float volume);
		void LoadOnThread(const std::string& path);*/

		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* m_pImpl;
	};
}


