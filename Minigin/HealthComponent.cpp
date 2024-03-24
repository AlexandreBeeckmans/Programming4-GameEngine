#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* pParent) :
	BaseComponent::BaseComponent{ pParent }
{

}

void dae::HealthComponent::RemoveLive()
{
	if (m_CurrentLives > 0)
		--m_CurrentLives;
}
