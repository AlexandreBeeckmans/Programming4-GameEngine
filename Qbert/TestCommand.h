#pragma once
#include <glm/vec2.hpp>

#include "Command.h"

namespace dae
{
	class Die final : public dae::GameObjectCommand
	{
	public:
		Die(GameObject* pObject);
		virtual void Execute() override;
	};

	class Score final : public GameObjectCommand
	{
	public:
		Score(GameObject* pObject);
		virtual void Execute() override;
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
}

