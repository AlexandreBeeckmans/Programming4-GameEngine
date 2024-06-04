#include "DeadFallComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

#include <glm/vec2.hpp>

#include "imgui.h"
#include "Minigin.h"

qbert::DeadFallComponent::DeadFallComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::DeadFallComponent::InitValues()
{
	m_VerticalSpeed = m_StartVerticalSpeed;
}

void qbert::DeadFallComponent::UpdateMovement()
{
	m_VerticalSpeed += m_Gravity * dae::EngineTime::GetInstance().GetDeltaTime();

	glm::vec2 fallMovement{
		0,
		-m_VerticalSpeed * dae::EngineTime::GetInstance().GetDeltaTime()
	};
	GetOwner()->Translate(fallMovement);
}

bool qbert::DeadFallComponent::IsOutOfMap() const
{
	return (GetOwner()->GetWorldPosition().y > static_cast<float>(dae::Minigin::GetWindowHeight()));
}
