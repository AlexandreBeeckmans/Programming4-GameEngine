#pragma once
#include <deque>
#include <string>

namespace dae
{
	using soundId = unsigned short;

	


	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const soundId id, const float volume) = 0;
		virtual void StopAll() = 0;

		virtual void Init() = 0;
		virtual void LoadSound(const std::string& path, const soundId id) = 0;
		virtual void Update() = 0;
	};
}


