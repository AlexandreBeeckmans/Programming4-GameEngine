#include "ScoreComponent.h"

#include <iostream>

#include "EventManager.h"
#include "EventTypes.h"
#include "GameObject.h"
#include "ScoreUIComponent.h"
#include "UIComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent, const int score) :
	BaseComponent::BaseComponent{ pParent },
	m_CurrentScore(score)
{
	// Add the function pointer to the EventManager without arguments
	EventManager::GetInstance().AddFunction(static_cast<int>(qbert::EventType::COILYDEATH), this, &ScoreComponent::IncrementScore, 500);
	EventManager::GetInstance().AddFunction(static_cast<int>(qbert::EventType::CATCHINGSLICK), this, &ScoreComponent::IncrementScore, 300);

}

void dae::ScoreComponent::InitObserver(qbert::ScoreUIComponent* pUiComponent)
{
	AddObserver(pUiComponent);
}

void dae::ScoreComponent::IncrementScore(int scoreToAdd)
{
	m_CurrentScore += scoreToAdd;
	NotifyObservers();
}


