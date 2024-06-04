#include "SlickDirection.h"

#include "GameObject.h"
#include "GridMoveComponent.h"

qbert::SlickDirection::SlickDirection(dae::GameObject* owner, MapComponent* pMap):
BaseComponent(owner),
m_pMap(pMap)
{
}

void qbert::SlickDirection::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
	ResetPosition();
}

void qbert::SlickDirection::SetMovementDirection() const
{

	const int randomDirection{ rand() % 2 };

	if(randomDirection == 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMLEFT);
		return;
	}
	m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMRIGHT);
	
}

void qbert::SlickDirection::ResetPosition() const
{
	m_pMoveComponent->SetCurrentIndexToTop();
	GetOwner()->SetLocalPosition
	(
		glm::vec2
		{
			m_pMap->GetTileByIndex(m_pMoveComponent->GetCurrentIndex())->GetStartPoint().x,
			m_pMap->GetTileByIndex(m_pMoveComponent->GetCurrentIndex())->GetStartPoint().y - 200
		}
	);
}
