#include "CoilyState.h"

#include "EngineTime.h"

#include "CoilyFSMManagerComponent.h"
#include "GridMoveComponent.h"
#include "FallComponent.h"
#include "FollowPlayerComponent.h"
#include "KillerComponent.h"
#include "CoilyAnimatorComponent.h"


void qbert::CoilyState::Enter(dae::GameObject& coilyObject)
{
	m_pMoveComponent = coilyObject.GetComponent<GridMoveComponent>();
	m_pCoilyComponent = coilyObject.GetComponent<CoilyFSMManagerComponent>();
	m_pFallComponent = coilyObject.GetComponent<FallComponent>();
	m_pFollowPlayerComponent = coilyObject.GetComponent<FollowPlayerComponent>();
	m_pKillerComponent = coilyObject.GetComponent<KillerComponent>();
	m_pAnimatorComponent = coilyObject.GetComponent<CoilyAnimatorComponent>();
}

std::unique_ptr<qbert::CoilyState> qbert::CoilyWaitingState::HandleTransitions()
{
	if (m_CurrentWaitingTime >= m_MaxWaitingTime) return std::make_unique<CoilyJumpingState>();

	return nullptr;
}

void qbert::CoilyWaitingState::Update()
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	GetKillerComponent()->CheckForPlayer();
}

void qbert::CoilyWaitingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);
	m_CurrentWaitingTime = 0.0f;
	GetMoveComponent()->ResetPositionValues();
	GetAnimatorComponent()->SetWaitingSprite();
}

std::unique_ptr<qbert::CoilyState> qbert::CoilyJumpingState::HandleTransitions()
{
	if (GetMoveComponent()->HasReachedFinalPosition()) return std::make_unique<CoilyWaitingState>();
	return nullptr;
}

void qbert::CoilyJumpingState::Update()
{
	GetMoveComponent()->UpdateMovement();
}

void qbert::CoilyJumpingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);

	GetFollowComponent()->SetMovementDirection();
	GetMoveComponent()->SetMovementDirection();
}

std::unique_ptr<qbert::CoilyState> qbert::CoilyArrivingState::HandleTransitions()
{
	if (GetFallComponent()->HasReachedFallPos())
	{
		return std::make_unique<CoilyWaitingState>();
	}
	return nullptr;
}

void qbert::CoilyArrivingState::Update()
{
	GetFallComponent()->UpdateFall();

	m_CurrentAnimTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_CurrentAnimTime >= m_MaxAnimTime)
	{
		m_CurrentAnimTime = 0;
		++m_AnimState %= 2;
		GetAnimatorComponent()->SetArrivingSprite(m_AnimState);
	}
}

void qbert::CoilyArrivingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);
	GetAnimatorComponent()->SetVisible();
	GetFallComponent()->SetFallDirection();
}

std::unique_ptr<qbert::CoilyState> qbert::CoilyPreparingState::HandleTransitions()
{
	if (m_CurrentPreparingTime >= m_MaxAnimTime) return std::make_unique<CoilyArrivingState>( );
	return nullptr;
}

void qbert::CoilyPreparingState::Update()
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}
