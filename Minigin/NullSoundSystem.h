#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem : public SoundSystem
	{
	public:
		virtual ~NullSoundSystem() override = default;
		virtual void Play(const soundId, const float) override{}
		virtual void StopAll() override{}

		virtual void Init() override{}
		virtual void LoadSound(const std::string&, const soundId) override{}
		virtual void Update() override{}

	};
}


