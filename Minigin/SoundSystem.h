#pragma once
#include <deque>
#include <string>

namespace dae
{
	using soundId = unsigned short;

	struct PlayMessageEvent
	{
		soundId id;
		float volume;
	};


	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const soundId id, const float volume);

		virtual void Init() = 0;
		virtual void LoadSound(const std::string& path) = 0;
		virtual void Update() = 0;


	protected:
		static std::deque<PlayMessageEvent>& GetPendingEvents() { return m_PendingEvents; }

	private:
		static std::deque<PlayMessageEvent> m_PendingEvents;
	};
}


