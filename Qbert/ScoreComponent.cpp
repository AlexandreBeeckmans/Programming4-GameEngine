#include "ScoreComponent.h"

#include <iostream>

#include "EventManager.h"
#include "EventTypes.h"
#include "GameObject.h"
#include "ScoreUIComponent.h"
#include "TileActivatorComponent.h"
#include "GridMoveComponent.h"
#include "UIComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent, const int score) :
	BaseComponent{ pParent },
	m_CurrentScore(score)
{
	// Add the function pointer to the EventManager without arguments
	EventManager::GetInstance().AddFunctionWithComp(static_cast<int>(qbert::EventType::COILYDEATH), this, this, &ScoreComponent::IncrementScore, 500);
	EventManager::GetInstance().AddFunctionWithComp(static_cast<int>(qbert::EventType::CATCHINGSLICK), GetOwner()->GetComponent<qbert::GridMoveComponent>(), this, &ScoreComponent::IncrementScore, 300);
	EventManager::GetInstance().AddFunctionWithComp(static_cast<int>(qbert::EventType::ACTIVATETILE), this, this, &ScoreComponent::IncrementScore, 25);
	EventManager::GetInstance().AddFunctionWithComp(static_cast<int>(qbert::EventType::REMAININGDISK), GetOwner()->GetComponent<qbert::TileActivatorComponent>(), this, &ScoreComponent::IncrementScore, 50);

}

void dae::ScoreComponent::InitObserver(qbert::ScoreUIComponent* pUiComponent)
{
	AddObserver(pUiComponent);
}

void dae::ScoreComponent::IncrementScore(int scoreToAdd)
{
	if (!IsOwnerActive()) return;
	m_CurrentScore += scoreToAdd;
	NotifyObservers();
}


