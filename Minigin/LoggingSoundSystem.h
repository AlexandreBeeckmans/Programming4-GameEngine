#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class LoggingSoundSystem final: public SoundSystem
	{
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem);
		virtual ~LoggingSoundSystem() override = default;

		virtual void Play(const soundId id, const float volume) override;
		virtual void Init() override;
		virtual void LoadSound(const std::string& path) override;
		virtual void Update() override;

	private:
		std::unique_ptr<SoundSystem> m_RealSoundSystem;
	};
}


