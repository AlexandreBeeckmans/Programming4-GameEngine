#pragma once
#include <glm/vec2.hpp>
#include "Command.h"
#include "GameObject.h"

namespace qbert
{
	class QbertMoveCommand : public dae::GameObjectCommand
	{
	public:
		QbertMoveCommand(dae::GameObject* pObject, const glm::vec2& direction);
		virtual void Execute() override;
	private:
		glm::vec2 m_Direction;
	};

	class GoNextSceneCommand : public dae::Command
	{
	public:
		GoNextSceneCommand() = default;
		virtual void Execute() override;
	};

	class SkipLevelCommand : public dae::Command
	{
	public:
		SkipLevelCommand() = default;
		virtual void Execute() override;
	};

	class IncrementLetterCommand : public dae::GameObjectCommand
	{
	public:
		IncrementLetterCommand(dae::GameObject* pObject, const int direction);
		virtual void Execute() override;
	private:
		int m_Direction{};
	};

	class IncrementLetterIndexCommand : public dae::GameObjectCommand
	{
	public:
		IncrementLetterIndexCommand(const int direction, dae::GameObject* pObject, const std::vector<dae::GameObject*>& pArrow);
		virtual void Execute() override;
	private:
		std::vector<dae::GameObject*> m_pArrow{};
		int m_Direction{ 0 };
	};

	class SelectCommand : public dae::GameObjectCommand
	{
	public:
		SelectCommand(dae::GameObject* pObject, int direction, const float discplacement);
		virtual void Execute() override;
	private :
		int m_Direction;
		float m_Discplacement;
	};
}


