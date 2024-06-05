#include "KillerComponent.h"

#include "GameObject.h"

#include "GridMoveComponent.h"
#include "KillableComponent.h"

qbert::KillerComponent::KillerComponent(dae::GameObject* owner, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects):
BaseComponent(owner)
{
	for (auto& player : *pPlayerObjects)
	{
		m_pPlayerMoveComponents.push_back(player->GetComponent<GridMoveComponent>());
		m_pPlayerKillableComponents.push_back(player->GetComponent<KillableComponent>());
	}
	
}

void qbert::KillerComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::KillerComponent::CheckForPlayer() const
{
	for(size_t i{0}; i < m_pPlayerMoveComponents.size(); ++i)
	{
		if (m_pPlayerMoveComponents[i]->GetCurrentIndex() == m_pMoveComponent->GetCurrentIndex() && m_pPlayerMoveComponents[i]->IsOwnerActive())
		{
			m_pPlayerKillableComponents[i]->EncountersEnemy();
		}
	}
	
}
