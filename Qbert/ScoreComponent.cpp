#include "ScoreComponent.h"

#include "GameObject.h"
#include "ScoreUIComponent.h"
#include "UIComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent, const int score) :
	BaseComponent::BaseComponent{ pParent },
	m_CurrentScore(score)
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
