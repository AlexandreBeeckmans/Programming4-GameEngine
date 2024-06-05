#include "ScoreUIComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"

qbert::ScoreUIComponent::ScoreUIComponent(dae::GameObject* pOwner, dae::TextComponent* pScoreText, const int playerNb) :
ImageComponent{pOwner, "qbert/Player Titles.png", true, 0, 0, 2, 1, playerNb},
m_pScoreText{pScoreText}
{
	m_pScoreText->SetText("0");

}

void qbert::ScoreUIComponent::Init()
{
	UpdateObserver();
}

void qbert::ScoreUIComponent::UpdateObserver()
{
	int score{m_pScoreComponent->GetScore()};
	m_pScoreText->SetText(std::to_string(score));
}

void qbert::ScoreUIComponent::SetScoreComponent(dae::ScoreComponent* pScoreComponent)
{
	m_pScoreComponent = pScoreComponent;
}
