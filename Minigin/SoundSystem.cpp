#include "SoundSystem.h"

#include <cassert>

std::deque<dae::PlayMessageEvent> dae::SoundSystem::m_PendingEvents{};

void dae::SoundSystem::Play(const soundId id, const float volume)
{
    for (PlayMessageEvent& event : m_PendingEvents)
    {
        if (event.id == id)
        {
            // Use the larger of the two volumes.
            event.volume = std::max(volume, event.volume);

            // Don't need to enqueue.
            return;
        }
    }
    m_PendingEvents.push_back({ id, volume });
}
