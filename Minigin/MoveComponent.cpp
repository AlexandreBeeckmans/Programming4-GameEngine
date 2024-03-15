#include "MoveComponent.h"
#include "Time.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* pParent, const float speed) :
	BaseComponent{ pParent },
	m_Speed{ speed }
{}

void dae::MoveComponent::Update()
{
	glm::vec3 currentPos{ GetOwner()->GetLocalPosition()};
	currentPos.x += Time::GetInstance().GetDeltaTime() * m_Speed * m_Movement.x;
	currentPos.y += Time::GetInstance().GetDeltaTime() * m_Speed * m_Movement.y;

	GetOwner()->SetLocalPosition(currentPos);
}

void dae::MoveComponent::SetMovement(const glm::vec2& movement, const bool isXAxis)
{
	if (isXAxis)
	{
		if (movement.x > 0)
		{
			m_Movement.x = 1;
			return;
		}
			
		if (movement.x < 0)
		{
			m_Movement.x = -1;
			return;
		}

		m_Movement.x = 0;
		return;
	}
	

	if (movement.y > 0)
	{
		m_Movement.y = 1;
		return;
	}
		
	if (movement.y < 0)
	{
		m_Movement.y = -1;
		return;
	}
		
	m_Movement.y = 0;

}