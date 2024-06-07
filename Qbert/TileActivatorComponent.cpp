#include "TileActivatorComponent.h"

#include "EventManager.h"
#include "EventTypes.h"
#include "GameObject.h"
#include "MapComponent.h"
#include "GridMoveComponent.h"

#include "ScoreComponent.h"

qbert::TileActivatorComponent::TileActivatorComponent(dae::GameObject* owner, qbert::MapComponent* pMap) :
BaseComponent(owner),
m_pMap(pMap)
{
}

void qbert::TileActivatorComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
	m_pScoreComponent = GetOwner()->GetComponent<dae::ScoreComponent>();
}

bool qbert::TileActivatorComponent::HasCompletedMap() const
{
	return m_pMap->IsComplete();
}

void qbert::TileActivatorComponent::ActivateCurrentTile() const
{
	if (!m_pMoveComponent->GetCurrentTile()) return;

	if (!m_pMoveComponent->GetCurrentTile()->IsCompleted())
	{
		dae::EventManager::GetInstance().CallFunctionFromComponent(static_cast<int>(qbert::EventType::ACTIVATETILE), m_pScoreComponent);
	}

	m_pMap->ActivateTileAtIndex(m_pMoveComponent->GetCurrentIndex());
}

void qbert::TileActivatorComponent::AnimateTiles() const
{
	m_pMap->SetAllTileAnimated(true);
}

bool qbert::TileActivatorComponent::IsOnTeleporter() const
{
	return m_pMap->IsOnATeleporter(GetOwner());
}

void qbert::TileActivatorComponent::ProcessWin() const
{
	for(int i{0}; i < m_pMap->GetRemainingDisks(); ++i)
	{
		dae::EventManager::GetInstance().CallFunctionFromComponent(static_cast<int>(qbert::EventType::REMAININGDISK), this);
	}
}
