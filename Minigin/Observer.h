#pragma once
#include <cstdint>
#include <iostream>

enum EventType 
{
	PLAYER_DIED
};

struct Event 
{
	static const uint8_t MAX_ARGS = 8;

	EventType m_type;
	//uint8_t m_numArgs;
	//EventArg m_args[MAX_ARGS];
};


namespace dae
{
	class Subject;
	class TextComponent;
	class GameObject;

	class BaseObserver
	{
	public:
		BaseObserver() = default;
		virtual ~BaseObserver() = default;

		BaseObserver(const BaseObserver& other) = delete;
		BaseObserver(BaseObserver&& other) = delete;
		BaseObserver& operator=(const BaseObserver& other) = delete;
		BaseObserver& operator=(BaseObserver&& other) = delete;


		virtual void Notify(Event event, GameObject* pObject) = 0;
	};

	class GameActionsObserver final : public BaseObserver
	{
	public:

		GameActionsObserver() = default;
		GameActionsObserver(TextComponent* pTextComponent);
		virtual ~GameActionsObserver() = default;

		GameActionsObserver(const GameActionsObserver& other) = default;
		GameActionsObserver(GameActionsObserver&& other) = default;
		GameActionsObserver& operator=(const GameActionsObserver& other) = default;
		GameActionsObserver& operator=(GameActionsObserver&& other) = default;

		virtual void Notify(Event event, GameObject* pObject) override;

	private:
		TextComponent* m_pRelatedTextComponent{};
	};

}



