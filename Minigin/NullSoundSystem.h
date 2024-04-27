#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem : public SoundSystem
	{
	public:
		virtual ~NullSoundSystem() override = default;
		void Play(const soundId, const float) override{}
		void Init() override{}
		void LoadSound(const std::string&) override{}

	};
}


