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
}


