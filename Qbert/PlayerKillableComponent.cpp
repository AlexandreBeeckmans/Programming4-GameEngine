#include "PlayerKillableComponent.h"

#include "GameObject.h"

#include "GridMoveComponent.h"

qbert::PlayerKillableComponent::PlayerKillableComponent(dae::GameObject* owner, GridMoveComponent* pPlayerMoveComponent) :
BaseComponent(owner),
m_pPlayerMoveComponent(pPlayerMoveComponent)
{
}

void qbert::PlayerKillableComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

bool qbert::PlayerKillableComponent::IsEncounteringPlayer() const
{
	return m_pPlayerMoveComponent->GetCurrentIndex() == m_pMoveComponent->GetCurrentIndex();
}
