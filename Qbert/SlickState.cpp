#include "SlickState.h"

#include <random>

#include "DeadFallComponent.h"
#include "EngineTime.h"
#include "FallComponent.h"
#include "GridMoveComponent.h"
#include "SlickDirection.h"
#include "TileDeactivatorComponent.h"
#include "PlayerKillableComponent.h"
#include "SlickAnimatorComponent.h"


void qbert::SlickState::Enter(dae::GameObject& slickObject)
{
	m_pFallComponent = slickObject.GetComponent<FallComponent>();
	m_pDirectionComponent = slickObject.GetComponent<SlickDirection>();
	m_pMoveComponent = slickObject.GetComponent<GridMoveComponent>();
	m_pDeactivatorComponent = slickObject.GetComponent<TileDeactivatorComponent>();
	m_pKillableComponent = slickObject.GetComponent<PlayerKillableComponent>();
	m_pDeadFallComponent = slickObject.GetComponent<DeadFallComponent>();
	m_pAnimatorComponent = slickObject.GetComponent<SlickAnimatorComponent>();
}

std::unique_ptr<qbert::SlickState> qbert::SlickPreparingState::HandleTransitions()
{
	if (m_CurrentPreparingTime < m_PreparingTime) return nullptr;

	return std::make_unique<SlickFallingState>();
}

void qbert::SlickPreparingState::Update()
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::SlickPreparingState::Enter(dae::GameObject& slickObject)
{
	SlickState::Enter(slickObject);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(2.0f, m_MaxPreparingTime);
	m_PreparingTime = static_cast<float>(dis(gen));
}

std::unique_ptr<qbert::SlickState> qbert::SlickFallingState::HandleTransitions()
{
	if(!GetFallComponent()->HasReachedFallPos())return nullptr;
	return std::make_unique<SlickWaitingState>();
}

void qbert::SlickFallingState::Update()
{
	GetFallComponent()->UpdateFall();
}

void qbert::SlickFallingState::Enter(dae::GameObject& slickObject)
{
	SlickState::Enter(slickObject);
	GetFallComponent()->SetFallDirection();
}

std::unique_ptr<qbert::SlickState> qbert::SlickWaitingState::HandleTransitions()
{
	if (m_CurrentWaitingTime >= m_WaitingTime) return std::make_unique<SlickJumpingState>();

	if (GetKillableComponent()->IsEncounteringPlayer()) return std::make_unique<SlickDyingState>();
	if (GetMoveComponent()->GetCurrentIndex() < 0) return std::make_unique<SlickDyingState>();

	return nullptr;
}

void qbert::SlickWaitingState::Update()
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::SlickWaitingState::Enter(dae::GameObject& slickObject)
{
	SlickState::Enter(slickObject);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, m_MaxWaitingTime);
	m_WaitingTime = static_cast<float>(dis(gen));

	GetMoveComponent()->ResetPositionValues();
	GetDeactivatorComponent()->DeactivateCurrentTile();
}

std::unique_ptr<qbert::SlickState> qbert::SlickJumpingState::HandleTransitions()
{
	if (GetMoveComponent()->HasReachedFinalPosition()) return std::make_unique<SlickWaitingState>();
	return nullptr;
}

void qbert::SlickJumpingState::Update()
{
	GetMoveComponent()->UpdateMovement();
}

void qbert::SlickJumpingState::Enter(dae::GameObject& slickObject)
{
	SlickState::Enter(slickObject);

	GetDirectionComponent()->SetMovementDirection();
	GetMoveComponent()->SetMovementDirection();
	GetAnimatorComponent()->SetSprite();
}

std::unique_ptr<qbert::SlickState> qbert::SlickDyingState::HandleTransitions()
{
	if(GetDeadFallComponent()->IsOutOfMap()) return std::make_unique<SlickPreparingState>();

	return nullptr;
}

void qbert::SlickDyingState::Enter(dae::GameObject& slickObject)
{
	SlickState::Enter(slickObject);
	GetDeadFallComponent()->InitValues();
}

void qbert::SlickDyingState::Update()
{
	GetDeadFallComponent()->UpdateMovement();
}

void qbert::SlickDyingState::Exit()
{
	GetDirectionComponent()->ResetPosition();
}
