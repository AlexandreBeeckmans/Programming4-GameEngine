#include "KillerComponent.h"

#include "GameObject.h"

#include "GridMoveComponent.h"
#include "KillableComponent.h"

qbert::KillerComponent::KillerComponent(dae::GameObject* owner, dae::GameObject* pPlayerObject):
BaseComponent(owner)
{
	m_pPlayerMoveComponent = pPlayerObject->GetComponent<GridMoveComponent>();
	m_pPlayerKillableComponent = pPlayerObject->GetComponent<KillableComponent>();
}

void qbert::KillerComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::KillerComponent::CheckForPlayer() const
{
	if (m_pPlayerMoveComponent->GetCurrentIndex() == m_pMoveComponent->GetCurrentIndex())
	{
		m_pPlayerKillableComponent->EncountersEnemy();
	}
}
