#pragma once
#include <glm/vec2.hpp>
#include "Command.h"

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


