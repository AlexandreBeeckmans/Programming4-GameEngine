#include "CoilyState.h"

#include "EngineTime.h"

qbert::CoilyState* qbert::CoilyWaitingState::HandleTransitions(const CoilyMoveComponent&)
{
	if (m_CurrentWaitingTime >= m_MaxWaitingTime) return new CoilyJumpingState{};

	return nullptr;
}

void qbert::CoilyWaitingState::Update(CoilyMoveComponent& coily)
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	coily.CheckForPlayer();
}

void qbert::CoilyWaitingState::Enter(CoilyMoveComponent& coily)
{
	m_CurrentWaitingTime = 0.0f;
	coily.ResetPositionValues();
	coily.SetWaitingSprite();
}

qbert::CoilyState* qbert::CoilyJumpingState::HandleTransitions(const CoilyMoveComponent& coily)
{
	if (coily.HasReachedFinalPosition()) return new CoilyWaitingState{};
	return nullptr;
}

void qbert::CoilyJumpingState::Update(CoilyMoveComponent& coily)
{
	coily.UpdateMovement();
}

void qbert::CoilyJumpingState::Enter(CoilyMoveComponent& coily)
{
	coily.SetMovementDirection();
}

qbert::CoilyState* qbert::CoilyArrivingState::HandleTransitions(const CoilyMoveComponent& coily)
{
	if (coily.IsArrived()) return new CoilyWaitingState{};
	return nullptr;
}

void qbert::CoilyArrivingState::Update(CoilyMoveComponent& coily)
{
	coily.UpdateArrivingMovement();

	m_CurrentAnimTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_CurrentAnimTime >= m_MaxAnimTime)
	{
		m_CurrentAnimTime = 0;
		++m_AnimState %= 2;
		coily.SetArrivingSprite(m_AnimState);
	}
}

void qbert::CoilyArrivingState::Enter(CoilyMoveComponent& coily)
{
	coily.SetVisible();
}

qbert::CoilyState* qbert::CoilyPreparingState::HandleTransitions(const CoilyMoveComponent&)
{
	if (m_CurrentPreparingTime >= m_MaxAnimTime) return new CoilyArrivingState{};
	return nullptr;
}

void qbert::CoilyPreparingState::Update(CoilyMoveComponent&)
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}
