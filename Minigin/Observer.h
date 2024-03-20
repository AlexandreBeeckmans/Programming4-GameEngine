#pragma once
#include <cstdint>
#include <iostream>

enum EventType {
	PLAYER_DIED
	//...
};

struct Event {
	static const uint8_t MAX_ARGS = 8;

	EventType m_type;
	uint8_t m_numArgs;
	//EventArg m_args[MAX_ARGS];
};


namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		//virtual void Notify(Event event, GameObject* pObject) = 0;
	};

	class GameActions : public Observer
	{
	public:
		//void Notify(Event event, GameObject* pObject) override
		//{
		//	switch (event.m_type) {
		//	case EventType::PLAYER_DIED:
		//		//Decrement Lives
		//		std::cout << "Player died" << std::endl;
		//		break;
		//	}
		//}
	};

}



