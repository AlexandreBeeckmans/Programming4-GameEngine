#include "HealthComponent.h"
#include "GameObject.h"
#include "UIComponent.h"

dae::HealthComponent::HealthComponent(GameObject* pParent, const int livesRemaining) :
	BaseComponent::BaseComponent{ pParent },
m_CurrentLives(livesRemaining)
{

}

void dae::HealthComponent::RemoveLive()
{
	if (m_CurrentLives > 0)
	{
		--m_CurrentLives;
		NotifyObservers();
		return;
	}

	m_IsDead = true;
}
