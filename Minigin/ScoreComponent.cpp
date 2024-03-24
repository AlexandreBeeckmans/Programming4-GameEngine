#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent) :
	BaseComponent::BaseComponent{ pParent }
{

}

void dae::ScoreComponent::IncrementScore(const int scoreToAdd)
{
	m_CurrentScore += scoreToAdd;
}
