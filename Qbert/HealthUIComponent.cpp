#include "HealthUIComponent.h"
#include "HealthComponent.h"
#include "ImageComponent.h"

qbert::HealthUIComponent::HealthUIComponent(dae::GameObject* pOwner, dae::ImageComponent* pImage) :
BaseComponent(pOwner),
m_pLivesImage(pImage)
{
}

void qbert::HealthUIComponent::UpdateObserver()
{
	int maxLives = m_pHealthComponent->GetMaxLives();
	int lives = m_pHealthComponent->GetLivesRemaining();
	m_pLivesImage->ReduceHeight(static_cast<float>(lives) / static_cast<float>(maxLives));
}

void qbert::HealthUIComponent::SetHealthComponent(dae::HealthComponent* pHealthComponent)
{
	m_pHealthComponent = pHealthComponent;
}
