#pragma once
#include <string>

namespace dae
{
	using soundId = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const soundId id, const float volume) = 0;
		virtual void Init() = 0;
		virtual void LoadSound(const std::string& path) = 0;
	};
}


