#include "HealthComponent.h"
#include "GameObject.h"
#include "UIComponent.h"

dae::HealthComponent::HealthComponent(GameObject* pParent, const int maxLives) :
	BaseComponent::BaseComponent{ pParent },
m_MaxLives(maxLives),
m_CurrentLives(maxLives)
{

}

void dae::HealthComponent::Init()
{
	/*if (auto ui{ GetOwner()->GetComponent<UIComponent>() })
	{
		AddObserver(ui);
	}*/
}

void dae::HealthComponent::RemoveLive()
{
	if (m_CurrentLives > 0)
	{
		--m_CurrentLives;
		NotifyObservers();
	}
		
}
