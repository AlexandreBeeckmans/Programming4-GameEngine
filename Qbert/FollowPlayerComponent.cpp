#include "FollowPlayerComponent.h"

#include "GameObject.h"
#include "GridMoveComponent.h"
#include "MapComponent.h"

qbert::FollowPlayerComponent::FollowPlayerComponent(dae::GameObject* owner, GridMoveComponent* pPlayerMovement,
	MapComponent* pMap):
BaseComponent(owner),
m_pPlayerMoveComponent(pPlayerMovement),
m_pMap(pMap)
{
}

void qbert::FollowPlayerComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::FollowPlayerComponent::SetMovementDirection() const
{
	const int playerRow = m_pMap->GetRowFromIndex(m_pPlayerMoveComponent->GetCurrentIndex());
	const int playerColumn = m_pMap->GetColumnFromIndex(m_pPlayerMoveComponent->GetCurrentIndex());

	const int coilyRow = m_pMap->GetRowFromIndex(m_pMoveComponent->GetCurrentIndex());
	const int coilyColumn = m_pMap->GetColumnFromIndex(m_pMoveComponent->GetCurrentIndex());


	if (playerRow < coilyRow)
	{
		if (playerColumn < coilyColumn)
		{
			m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMLEFT);
			GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(9);
			return;
		}
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMRIGHT);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(7);
		return;


	}

	if (playerColumn < coilyColumn)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPLEFT);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(5);
		return;
	}

	m_pMoveComponent->SetGridDirection(GridDirection::TOPRIGHT);
	GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
}
