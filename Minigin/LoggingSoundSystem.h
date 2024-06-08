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
		virtual void StopAll() override;

		virtual void Init() override;
		virtual void LoadSound(const std::string& path, const soundId id) override;
		virtual void Update() override;

	private:
		std::unique_ptr<SoundSystem> m_RealSoundSystem;
	};
}


