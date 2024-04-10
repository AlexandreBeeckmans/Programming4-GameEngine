#pragma once
#include <glm/vec2.hpp>


namespace dae
{
	class GameObject;
	class TextComponent;

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

		Move(dae::GameObject* pActor, const glm::vec2& direction);
		virtual void Execute() override;

	private:
		glm::vec2 m_Direction;
		bool m_IsMoving = false;
	};

	class Die final : public GameObjectCommand
	{
	public:
		Die(dae::GameObject* pObject, TextComponent* pLivesText = nullptr);
		virtual void Execute() override;

	private:
		TextComponent* m_pLivesText{ nullptr };
	};

	class Score final : public GameObjectCommand
	{
	public:
		Score(GameObject* pObject, TextComponent* pLivesText = nullptr);
		virtual void Execute() override;

	private:
		TextComponent* m_pScoreText{ nullptr };
	};
}

