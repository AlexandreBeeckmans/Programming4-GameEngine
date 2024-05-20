#include "ScoreComponent.h"

#include "GameObject.h"
#include "ScoreUIComponent.h"
#include "UIComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent) :
	BaseComponent::BaseComponent{ pParent }
{

}

void dae::ScoreComponent::InitObserver(qbert::ScoreUIComponent* pUiComponent)
{
	AddObserver(pUiComponent);
}

void dae::ScoreComponent::IncrementScore(const int& scoreToAdd)
{
	m_CurrentScore += scoreToAdd;
	NotifyObservers();
}
