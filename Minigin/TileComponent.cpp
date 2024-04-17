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

