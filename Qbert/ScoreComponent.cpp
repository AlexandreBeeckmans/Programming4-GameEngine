#include "ScoreComponent.h"

#include "GameObject.h"
#include "UIComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent) :
	BaseComponent::BaseComponent{ pParent }
{

}

void dae::ScoreComponent::Init()
{
	if (auto ui{ GetOwner()->GetComponent<UIComponent>() })
	{
		AddObserver(ui);
	}
}

void dae::ScoreComponent::IncrementScore(const int& scoreToAdd)
{
	m_CurrentScore += scoreToAdd;
	NotifyObservers();
}
