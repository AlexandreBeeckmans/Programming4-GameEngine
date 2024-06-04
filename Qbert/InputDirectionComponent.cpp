#include "InputDirectionComponent.h"

#include "GameObject.h"

#include "GridMoveComponent.h"

qbert::InputDirectionComponent::InputDirectionComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::InputDirectionComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::InputDirectionComponent::Update()
{
	if(m_IsInputPressedThisFrame)
	{
		m_IsInputPressedThisFrame = false;
	}
}

void qbert::InputDirectionComponent::SetInputDirection(const glm::vec2& direction)
{
	m_IsInputPressedThisFrame = true;

	if (direction.x > 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMRIGHT);
	}

	if (direction.y < 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMLEFT);
	}

	if (direction.x < 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPLEFT);
	}

	if (direction.y > 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPRIGHT);
	}
}


