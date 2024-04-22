#include "RotatingComponent.h"

#include "GameObject.h"
#include "EngineTime.h"

#include <numbers>


dae::RotatingComponent::RotatingComponent(GameObject* pGameObject, const float speed, const float radius) :
	BaseComponent(pGameObject),
	m_Speed{speed},
	m_Radius{radius}
{
}

void dae::RotatingComponent::Update()
{
	m_Angle += m_Speed * EngineTime::GetInstance().GetDeltaTime();
	if (m_Angle >= 2 * std::numbers::pi_v<decltype(m_Angle)>)
		m_Angle -= 2 * std::numbers::pi_v<decltype(m_Angle)>;

	float newX{ m_Radius * cosf(m_Angle)};
	float newY{ m_Radius * sinf(m_Angle) };
		
	GetOwner()->SetLocalPosition(newX, newY);
}
