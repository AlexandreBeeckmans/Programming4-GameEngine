#include "RotatingComponent.h"

#include "GameObject.h"
#include "Time.h"

dae::RotatingComponent::RotatingComponent(GameObject* pGameObject, const float speed, const float radius) :
	BaseComponent(pGameObject),
	m_Speed{speed},
	m_Radius{radius}
{
	//The center of rotation is the current position of the player when init
	m_Center.x = GetOwner()->GetWorldPosition().x;
	m_Center.y = GetOwner()->GetWorldPosition().y;
}

void dae::RotatingComponent::Update()
{
	m_Angle += m_Speed * Time::GetInstance().GetDeltaTime();
	float newX{ m_Radius * cosf(m_Angle)};
	float newY{ m_Radius * sinf(m_Angle) };


	//If object has no parent, will turn around its world position
	if (!GetOwner()->GetParent())
	{
		newX += m_Center.x;
		newY += m_Center.y;
	}

	//So if the player has a parent, it will turn around its parent which is its 0;0 local position
		


	GetOwner()->SetLocalPosition(newX, newY);
}
