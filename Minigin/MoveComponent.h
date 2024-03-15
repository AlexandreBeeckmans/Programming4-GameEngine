#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		virtual void Update() override;

		MoveComponent(GameObject* m_pParent, const float speed = 100.0f);
		virtual ~MoveComponent() = default;
		MoveComponent(const MoveComponent& other) = default;
		MoveComponent(MoveComponent&& other) = default;
		MoveComponent& operator=(const MoveComponent& other) = default;
		MoveComponent& operator=(MoveComponent&& other) = default;

		void SetMovement(const glm::vec2& movement, const bool isXAxis);
		float GetSpeed() const { return m_Speed; };
	private:

		float m_Speed{ 100.0f };
		glm::vec2 m_Movement{ 0,0 };
	};
}


