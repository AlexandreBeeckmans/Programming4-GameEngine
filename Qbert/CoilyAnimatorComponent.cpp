#include "CoilyAnimatorComponent.h"

#include "GameObject.h"
#include "GridMoveComponent.h"

qbert::CoilyAnimatorComponent::CoilyAnimatorComponent(dae::GameObject* owner):
BaseComponent(owner)
{
}

void qbert::CoilyAnimatorComponent::Init()
{
	m_pImageComponent = GetOwner()->GetComponent<dae::ImageComponent>();
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();

	GetOwner()->GetComponent<dae::ImageComponent>()->SetVisible(false);
}

void qbert::CoilyAnimatorComponent::SetWaitingSprite() const
{
	const int currentCol{ m_pImageComponent->GetColumn() };

	if (currentCol > 0)
	{
		m_pImageComponent->SetColumn(currentCol - 1);
	}
	else
	{
		m_pImageComponent->SetColumn(2);
	}

}

void qbert::CoilyAnimatorComponent::SetArrivingSprite(const int column) const
{
	m_pImageComponent->SetColumn(column);
}

void qbert::CoilyAnimatorComponent::SetJumpingSprite() const
{
	switch(m_pMoveComponent->GetGridDirection())
	{
	case GridDirection::BOTTOMLEFT :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(9);
		return;
	case GridDirection::BOTTOMRIGHT:
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(7);
		return;
	case GridDirection::TOPLEFT:
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(5);
		return;
	case GridDirection::TOPRIGHT:
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		return;
	}
}

void qbert::CoilyAnimatorComponent::SetVisible() const
{
	m_pImageComponent->SetVisible(true);
}
