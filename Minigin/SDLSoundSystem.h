#pragma once

#include <memory>

#include "SoundSystem.h"

namespace dae
{
	struct PlayMessageEvent
	{
		soundId id;
		float volume;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;
		virtual void Play(const soundId id, const float volume) override;
		virtual void StopAll() override;

		virtual void Init() override;
		virtual void LoadSound(const std::string& path, const soundId id) override;
		virtual void Update() override;

	private:

		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* m_pImpl;
	};
}


