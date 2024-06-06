#include "KillableComponent.h"

#include "GameObject.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"

#include "BubbleManagerComponent.h"
#include "GridMoveComponent.h"
#include "HealthComponent.h"

qbert::KillableComponent::KillableComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::KillableComponent::Init()
{
	m_pBubbleComponent = GetOwner()->GetComponent<BubbleManagerComponent>();
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();

	m_pHealthComponent = GetOwner()->GetComponent<dae::HealthComponent>();
}

void qbert::KillableComponent::Update()
{
	if(m_EnemyEncounteredThisFrame)
	{
		m_EnemyEncounteredThisFrame = false;
	}
}

void qbert::KillableComponent::EncountersEnemy()
{
	m_EnemyEncounteredThisFrame = true;
}

void qbert::KillableComponent::Kill() const
{
	
	m_pBubbleComponent->ShowBubble(true);
	m_pHealthComponent->RemoveLive();
}

void qbert::KillableComponent::Respawn() const
{
	m_pMoveComponent->SetCurrentIndexToTop();
	GetOwner()->SetLocalPosition(m_pMoveComponent->GetCurrentTile()->GetStartPoint());
	m_pBubbleComponent->ShowBubble(false);
}
