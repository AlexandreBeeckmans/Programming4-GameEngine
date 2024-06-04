#include "TileDeactivatorComponent.h"

#include "GameObject.h"
#include "GridMoveComponent.h"

qbert::TileDeactivatorComponent::TileDeactivatorComponent(dae::GameObject* owner, MapComponent* pMap) :
	BaseComponent(owner),
	m_pMap(pMap)
{
}

void qbert::TileDeactivatorComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::TileDeactivatorComponent::DeactivateCurrentTile() const
{
	if (!m_pMoveComponent->GetCurrentTile()) return;
	m_pMoveComponent->GetCurrentTile()->Deactivate();
}
