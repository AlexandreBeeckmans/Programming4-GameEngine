#include "SlickAnimatorComponent.h"

#include "GameObject.h"

#include "ImageComponent.h"
#include"GridMoveComponent.h"

qbert::SlickAnimatorComponent::SlickAnimatorComponent(dae::GameObject* owner):
BaseComponent(owner)
{
}

void qbert::SlickAnimatorComponent::Init()
{
	m_pImageComponent = GetOwner()->GetComponent<dae::ImageComponent>();
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::SlickAnimatorComponent::SetSprite()
{
	if(m_pMoveComponent->GetGridDirection() == GridDirection::BOTTOMLEFT)
	{
		m_pImageComponent->SetColumn(0);
		return;
	}

	m_pImageComponent->SetColumn(1);
}
