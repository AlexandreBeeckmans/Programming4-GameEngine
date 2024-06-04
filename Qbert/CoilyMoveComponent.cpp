#include "CoilyMoveComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

#include "MapComponent.h"
#include "CoilyState.h"
#include "GridMoveComponent.h"

#include "KillableComponent.h"

qbert::CoilyMoveComponent::CoilyMoveComponent(dae::GameObject* owner, dae::GameObject* pPlayerObject, MapComponent* pMap) :
BaseComponent(owner),
m_pMap(pMap)
{
		m_pPlayerMoveComponent = pPlayerObject->GetComponent<GridMoveComponent>();
		m_pPlayerKillableComponent = pPlayerObject->GetComponent<KillableComponent>();

		m_State = new CoilyPreparingState{};
		m_State->Enter(*GetOwner());
}

void qbert::CoilyMoveComponent::Update()
{
	CoilyState* newState = m_State->HandleTransitions();
	if (newState)
	{
		m_State->Exit();
		delete m_State;
		m_State = newState;
		m_State->Enter(*GetOwner());
	}

	m_State->Update();

}

void qbert::CoilyMoveComponent::Init()
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetVisible(false);
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();

	m_ArrivingTarget = m_pMoveComponent->GetCurrentTile()->GetStartPoint() - glm::vec2{ 0, GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h / 2 };
	m_ArrivingDirection = glm::normalize(m_ArrivingTarget - glm::vec2{ GetWorldPosition() });
}

void qbert::CoilyMoveComponent::CheckForPlayer() const
{
	if (m_pPlayerMoveComponent->GetCurrentIndex() == m_pMoveComponent->GetCurrentIndex())
	{
		m_pPlayerKillableComponent->EncountersEnemy();
	}
}

bool qbert::CoilyMoveComponent::IsArrived() const
{
	const glm::vec2 currentPos
	{
		GetOwner()->GetWorldPosition().x,
		GetOwner()->GetWorldPosition().y
	};
	return glm::length(m_pMoveComponent->GetCurrentTile()->GetStartPoint() - currentPos) < 30.0f;
}

void qbert::CoilyMoveComponent::SetWaitingSprite() const
{
	const int currentCol{ GetOwner()->GetComponent<dae::ImageComponent>()->GetColumn() };

	if(currentCol > 0)
	{
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(currentCol-1);
	}
	else
	{
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
	}
		
}

void qbert::CoilyMoveComponent::SetArrivingSprite(const int column) const
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(column);
}

void qbert::CoilyMoveComponent::SetVisible() const
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetVisible(true);
}

void qbert::CoilyMoveComponent::SetMovementDirection()
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

void qbert::CoilyMoveComponent::UpdateArrivingMovement() const
{
	constexpr float speed = 55.0f;
	GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_ArrivingDirection);
}
