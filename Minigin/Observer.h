#pragma once
#include <cstdint>

#include "BaseComponent.h"

enum EventType 
{
	PLAYER_DIED,
	PLAYER_SCORED,
	PLAYER_WIN
};


struct Event 
{
	static const uint8_t MAX_ARGS = 8;

	EventType m_type;
	uint8_t m_numArgs;
	dae::BaseComponent* m_args[MAX_ARGS];
};

namespace dae
{
	class Subject;
	class TextComponent;
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void UpdateObserver() {}
	};
}



