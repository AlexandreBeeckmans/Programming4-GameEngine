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
		IncrementLetterCommand(dae::GameObject* pObject);
		virtual void Execute() override;
	};

	class IncrementLetterIndexCommand : public dae::GameObjectCommand
	{
	public:
		IncrementLetterIndexCommand(dae::GameObject* pObject);
		virtual void Execute() override;
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


