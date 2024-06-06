#include "UggStates.h"

#include "EngineTime.h"

#include "FallComponent.h"
#include "GridMoveComponent.h"
#include "KillerComponent.h"
#include "DeadFallComponent.h"
#include "UggDirectionComponent.h"


void qbert::UggState::Enter(dae::GameObject& coilyObject)
{
	m_pMoveComponent = coilyObject.GetComponent<GridMoveComponent>();
	m_pFallComponent = coilyObject.GetComponent<FallComponent>();
	m_pKillerComponent = coilyObject.GetComponent<KillerComponent>();
	m_pDeadFallComponent = coilyObject.GetComponent<DeadFallComponent>();
	m_pDirectionComponent = coilyObject.GetComponent<UggDirectionComponent>();
}

std::unique_ptr<qbert::UggState> qbert::UggArrivingState::HandleTransitions()
{
	if (GetFallComponent()->HasReachedFallPos()) return std::make_unique<UggWaitingState>();
	return nullptr;
}

void qbert::UggArrivingState::Update()
{
	GetFallComponent()->UpdateFall();
}

void qbert::UggArrivingState::Enter(dae::GameObject& coilyObject)
{
	UggState::Enter(coilyObject);
	GetDirectionComponent()->ResetPosition();
	GetFallComponent()->SetFallDirection();
	

}

std::unique_ptr<qbert::UggState> qbert::UggPreparingState::HandleTransitions()
{
	if (m_CurrentPreparingTime < m_MaxPreparingTime) return nullptr;
	return std::make_unique<UggArrivingState>();
}

void qbert::UggPreparingState::Update()
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::UggPreparingState::Enter(dae::GameObject& coilyObject)
{
	UggState::Enter(coilyObject);
	GetDirectionComponent()->ResetPosition();
}

std::unique_ptr<qbert::UggState> qbert::UggWaitingState::HandleTransitions()
{
	if (m_CurrentPreparingTime >= m_MaxWaitingTime) return std::make_unique<UggMovingState>();

	if (GetMoveComponent()->GetCurrentIndex() == -1 || GetMoveComponent()->IsOnTop() ) return std::make_unique<UggDyingState>();

	return nullptr;
}

void qbert::UggWaitingState::Update()
{
	m_CurrentPreparingTime += dae::EngineTime::GetInstance().GetDeltaTime();

	GetKillerComponent()->CheckForPlayer();
}

std::unique_ptr<qbert::UggState> qbert::UggMovingState::HandleTransitions()
{
	if (GetFallComponent()->HasReachedFallPos()) return std::make_unique<UggWaitingState>();
	return nullptr;
}

void qbert::UggMovingState::Update()
{
	GetFallComponent()->UpdateFall();
}

void qbert::UggMovingState::Enter(dae::GameObject& coilyObject)
{
	UggState::Enter(coilyObject);

	//Set Ugg Direction
	GetDirectionComponent()->SetMovementDirection();

	if(GetMoveComponent()->GetCurrentIndex() >= 0)
	{
		GetFallComponent()->SetFallDirection();
	}
	
}

std::unique_ptr<qbert::UggState> qbert::UggDyingState::HandleTransitions()
{
	if (m_CurrentDyingTime < m_MaxDyingTime) return nullptr;
	return std::make_unique<UggArrivingState>();

}

void qbert::UggDyingState::Update()
{
	m_CurrentDyingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	GetDeadFallComponent()->UpdateMovement();
}
