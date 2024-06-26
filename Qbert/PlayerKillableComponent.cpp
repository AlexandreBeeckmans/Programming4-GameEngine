#include "PlayerKillableComponent.h"

#include "EventManager.h"
#include "EventTypes.h"
#include "GameObject.h"

#include "GridMoveComponent.h"

qbert::PlayerKillableComponent::PlayerKillableComponent(dae::GameObject* owner, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects) :
BaseComponent(owner)
{
	for (auto& player : *pPlayerObjects)
	{
		m_pPlayerMoveComponents.push_back(player->GetComponent<GridMoveComponent>());
	}
}

void qbert::PlayerKillableComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

bool qbert::PlayerKillableComponent::IsEncounteringPlayer() const
{
	for (auto playerMove : m_pPlayerMoveComponents)
	{
		if (playerMove->GetCurrentIndex() == m_pMoveComponent->GetCurrentIndex() && playerMove->IsOwnerActive())
		{
			dae::EventManager::GetInstance().CallFunctionFromComponent(static_cast<int>(qbert::EventType::CATCHINGSLICK), playerMove);
			return true;
		}
			
	}
	return false;
}
