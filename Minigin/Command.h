#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};


	class GameObjectCommand : public Command
	{
	private:
		GameObject* m_pActor;
	protected:
		GameObject* GetGameActor() const { return m_pActor; }
	public:

		GameObjectCommand(GameObject* pActor);
		virtual ~GameObjectCommand() = default;
	};

	class Move final : public GameObjectCommand
	{
	public:

		Move(dae::GameObject* pActor, const glm::vec2& speed);
		virtual void Execute() override;

	private:
		glm::vec2 m_Speed;
	};
}

