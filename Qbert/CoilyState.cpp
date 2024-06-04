#include "CoilyState.h"

#include "EngineTime.h"

#include "CoilyMoveComponent.h"
#include "GridMoveComponent.h"

void qbert::CoilyState::Enter(dae::GameObject& coilyObject)
{
	m_pMoveComponent = coilyObject.GetComponent<GridMoveComponent>();
	m_pCoilyComponent = coilyObject.GetComponent<CoilyMoveComponent>();
}

qbert::CoilyState* qbert::CoilyWaitingState::HandleTransitions()
{
	if (m_CurrentWaitingTime >= m_MaxWaitingTime) return new CoilyJumpingState{};

	return nullptr;
}

void qbert::CoilyWaitingState::Update()
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	GetCoilyComponent()->CheckForPlayer();
}

void qbert::CoilyWaitingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);
	m_CurrentWaitingTime = 0.0f;
	GetMoveComponent()->ResetPositionValues();
	GetCoilyComponent()->SetWaitingSprite();
}

qbert::CoilyState* qbert::CoilyJumpingState::HandleTransitions()
{
	if (GetMoveComponent()->HasReachedFinalPosition()) return new CoilyWaitingState{};
	return nullptr;
}

void qbert::CoilyJumpingState::Update()
{
	GetMoveComponent()->UpdateMovement();
}

void qbert::CoilyJumpingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);

	GetCoilyComponent()->SetMovementDirection();
	GetMoveComponent()->SetMovementDirection();
}

qbert::CoilyState* qbert::CoilyArrivingState::HandleTransitions()
{
	if (GetCoilyComponent()->IsArrived())
	{
		return new CoilyWaitingState{};
	}
	return nullptr;
}

void qbert::CoilyArrivingState::Update()
{
	GetCoilyComponent()->UpdateArrivingMovement();

	m_CurrentAnimTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_CurrentAnimTime >= m_MaxAnimTime)
	{
		m_CurrentAnimTime = 0;
		++m_AnimState %= 2;
		GetCoilyComponent()->SetArrivingSprite(m_AnimState);
	}
}

void qbert::CoilyArrivingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);
	GetCoilyComponent()->SetVisible();
}

qbert::CoilyState* qbert::CoilyPreparingState::HandleTransitions()
{
	if (m_CurrentPreparingTime >= m_MaxAnimTime) return new CoilyArrivingState{};
	return nullptr;
}

void qbert::CoilyPreparingState::Update()
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}
