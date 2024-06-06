#include "UggDirectionComponent.h"

#include "GameObject.h"

#include"GridMoveComponent.h"
#include "Minigin.h"

qbert::UggDirectionComponent::UggDirectionComponent(dae::GameObject* owner, MapComponent* pMap, bool isLeft):
BaseComponent(owner),
m_pMap(pMap),
m_isLeft(isLeft)
{
}

void qbert::UggDirectionComponent::Init()
{
	if(!m_pMoveComponent)
		m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::UggDirectionComponent::SetMovementDirection()
{

	int nextIndex{};
	int indexIncrementation{ m_isLeft ? 1 : -1 };

	if(m_MovementState == 1)
	{
		if(m_isLeft)
		{
			nextIndex = m_pMap->GetTopRightIndex(m_pMoveComponent->GetCurrentIndex());
		}
		else
		{
			nextIndex = m_pMap->GetTopLeftIndex(m_pMoveComponent->GetCurrentIndex());
		}
		
	}
	else
	{
		
		nextIndex = m_pMoveComponent->GetCurrentIndex() + indexIncrementation;
	}
	

	if(m_pMap->AreIndexesOnTheSameRow(nextIndex - indexIncrementation, nextIndex))
	{
		m_pMoveComponent->SetCurrentIndex(nextIndex);


		++m_MovementState %= 2;
		return;
	}



	m_pMoveComponent->SetCurrentIndex(-1);
	
}

void qbert::UggDirectionComponent::ResetPosition()
{
	if(!m_pMoveComponent)
	{
		m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
	}

	const int startIndex{ m_isLeft ? 0 : m_pMap->GetNbRows() - 1 };

	m_pMoveComponent->SetCurrentIndex(startIndex);
	GetOwner()->SetLocalPosition
	(
		glm::vec2
		{
			m_pMap->GetTileByIndex(m_pMoveComponent->GetCurrentIndex())->GetStartPoint().x,
			m_pMap->GetTileByIndex(m_pMoveComponent->GetCurrentIndex())->GetStartPoint().y + dae::Minigin::GetWindowWidth() + 200
		}
	);
}
