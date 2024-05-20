#include "TileComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"

qbert::TileComponent::TileComponent(dae::GameObject* m_pParent) :
	BaseComponent(m_pParent)
{}

bool qbert::TileComponent::IsCompleted() const
{
	return m_CurrentState >= (m_MaxState - 1);
}

void qbert::TileComponent::UpdateTile()
{
	if(!IsCompleted())
	{
		++m_CurrentState;
		GetOwner()->GetComponent<dae::ImageComponent>()->UpdateRow();
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

