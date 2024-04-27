#pragma once
#include <SDL_mixer.h>
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

	private:
		std::vector<Mix_Chunk*> m_AudioClips;
	};
}


