#include "TileComponent.h"

#include "AnimatorComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"

qbert::TileComponent::TileComponent(dae::GameObject* m_pParent, const int maxStates, const bool isReversible) :
	BaseComponent(m_pParent),
	m_MaxState(maxStates),
	m_IsReversible(isReversible)
{}

bool qbert::TileComponent::IsCompleted() const
{
	return m_CurrentState >= (m_MaxState);
}

void qbert::TileComponent::UpdateTile()
{
	if(!IsCompleted())
	{
		++m_CurrentState;
		GetOwner()->GetComponent<dae::ImageComponent>()->UpdateRow();
	}
	else
	{
		if(m_IsReversible)
		{
			m_CurrentState = 0;
			GetOwner()->GetComponent<dae::ImageComponent>()->SetRow(0);
		}
	}
}

glm::vec2 qbert::TileComponent::GetStartPoint() const
{
	dae::ImageComponent* pImageComp = GetOwner()->GetComponent<dae::ImageComponent>();
	glm::vec2 posToReturn
	{
		GetOwner()->GetWorldPosition().x + static_cast<float>(pImageComp->GetShape().w) / 4.0f,
		GetOwner()->GetWorldPosition().y - static_cast<float>(pImageComp->GetShape().h) / 4.0f
	};
	return posToReturn;
}

int qbert::TileComponent::GetWidth() const
{
	return static_cast<int>(static_cast<float>(GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().w) / dae::ImageComponent::GetSpriteScale());
}

int qbert::TileComponent::GetHeight() const
{
	return static_cast<int>(static_cast<float>(GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h) / dae::ImageComponent::GetSpriteScale());
}

void qbert::TileComponent::SetAnimated(const bool isAnimated)
{
	GetOwner()->GetComponent<dae::AnimatorComponent>()->SetActive(isAnimated);
}

