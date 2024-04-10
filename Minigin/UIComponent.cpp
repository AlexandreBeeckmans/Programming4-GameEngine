#include "UIComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

dae::UIComponent::UIComponent(GameObject* m_pParent, TextComponent* pScoreTextComponent, TextComponent* pLifeTextComponent): BaseComponent(m_pParent), Observer(),
	m_ScoreTextComponent{ pScoreTextComponent },
	m_LifeTextComponent{ pLifeTextComponent }
{
}

void dae::UIComponent::UpdateObserver()
{
	const int score{ GetOwner()->GetComponent<ScoreComponent>()->GetScore() };
	const std::string scoreString{ "Score :" + std::to_string(score) };
	m_ScoreTextComponent->SetText(scoreString);

	const int life{ GetOwner()->GetComponent<HealthComponent>()->GetLivesRemaining() };
	const std::string lifeString{ "Life : " + std::to_string(life) };
	m_LifeTextComponent->SetText(lifeString);
}
