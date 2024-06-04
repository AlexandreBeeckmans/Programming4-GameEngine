#include "CoilyAnimatorComponent.h"

#include "GameObject.h"

qbert::CoilyAnimatorComponent::CoilyAnimatorComponent(dae::GameObject* owner):
BaseComponent(owner)
{
}

void qbert::CoilyAnimatorComponent::Init()
{
	m_pImageComponent = GetOwner()->GetComponent<dae::ImageComponent>();
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

void qbert::CoilyAnimatorComponent::SetVisible() const
{
	m_pImageComponent->SetVisible(true);
}