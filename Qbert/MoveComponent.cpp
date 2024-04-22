#include "MoveComponent.h"
#include "EngineTime.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* pParent, const float speed) :
	BaseComponent{ pParent },
	m_Speed{ speed }
{}

void dae::MoveComponent::Update()
{
	glm::vec3 currentPos{ GetOwner()->GetLocalPosition()};
	currentPos.x += EngineTime::GetInstance().GetDeltaTime() * m_Speed * m_Movement.x;
	currentPos.y += EngineTime::GetInstance().GetDeltaTime() * m_Speed * m_Movement.y;

	GetOwner()->SetLocalPosition(currentPos);
}

void dae::MoveComponent::SetMovement(const glm::vec2& movement)
{
	m_Movement += movement;
}