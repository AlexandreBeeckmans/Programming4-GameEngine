#include "HealthComponent.h"
#include "GameObject.h"
#include "UIComponent.h"

dae::HealthComponent::HealthComponent(GameObject* pParent) :
	BaseComponent::BaseComponent{ pParent }
{

}

void dae::HealthComponent::Init()
{
	if (auto ui{ GetOwner()->GetComponent<UIComponent>() })
	{
		AddObserver(ui);
	}
}

void dae::HealthComponent::RemoveLive()
{
	if (m_CurrentLives > 0)
	{
		--m_CurrentLives;
		NotifyObservers();
	}
		
}
