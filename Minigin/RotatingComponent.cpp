#include "RotatingComponent.h"

#include "GameObject.h"
#include "Time.h"

dae::RotatingComponent::RotatingComponent(GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
	if (!GetOwner()->GetParent())
	{
		m_CenterX = GetOwner()->GetWorldPosition().x;
		m_CenterY = GetOwner()->GetWorldPosition().y;
	}
}

void dae::RotatingComponent::Update()
{
	
	/*GetOwner()->GetWorldPosition().x;
	GetOwner()->GetWorldPosition().y;*/

	m_Angle += m_Speed * Time::GetInstance().GetDeltaTime();
	float newX{ m_Radius * cosf(m_Angle)};
	float newY{ m_Radius * sinf(m_Angle) };

	if ((!GetOwner()->GetParent()))
	{
		newX += m_CenterX;
		newY += m_CenterY;
	}
		


	GetOwner()->SetPosition(newX, newY);
}
