#include "CoilyState.h"

#include "EngineTime.h"

#include "GridMoveComponent.h"
#include "FallComponent.h"
#include "FollowPlayerComponent.h"
#include "KillerComponent.h"
#include "CoilyAnimatorComponent.h"
#include "DeadFallComponent.h"
#include "EventManager.h"
#include "EventTypes.h"
#include "InputDirectionComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"


void qbert::CoilyState::Enter(dae::GameObject& coilyObject)
{
	m_pMoveComponent = coilyObject.GetComponent<GridMoveComponent>();
	m_pFallComponent = coilyObject.GetComponent<FallComponent>();
	m_pFollowPlayerComponent = coilyObject.GetComponent<FollowPlayerComponent>();
	m_pKillerComponent = coilyObject.GetComponent<KillerComponent>();
	m_pAnimatorComponent = coilyObject.GetComponent<CoilyAnimatorComponent>();
	m_pInputComponent = coilyObject.GetComponent<InputDirectionComponent>();
	m_pDeadFallComponent = coilyObject.GetComponent<DeadFallComponent>();
}

std::unique_ptr<qbert::CoilyState> qbert::CoilyWaitingState::HandleTransitions()
{
	if(GetFollowComponent())
	{
		if (m_CurrentWaitingTime >= m_MaxWaitingTime) return std::make_unique<CoilyJumpingState>();
	}

	if(GetInputComonent())
	{
		if (GetInputComonent()->IsInputPressedThisFrame()) return std::make_unique<CoilyJumpingState>();
	}

	if(GetMoveComponent()->GetCurrentIndex() == -1)
	{
		dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::COILYFALL), 100.0f);
		return std::make_unique<CoilyDyingState>();
	}

	

	return nullptr;
}

void qbert::CoilyWaitingState::Update()
{
	if(GetFollowComponent())
	{
		m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	}
	
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

	if(GetFollowComponent())
	{
		GetFollowComponent()->SetMovementDirection();
	}

	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::COILYJUMP), 100.0f);
	GetMoveComponent()->SetMovementDirection();
	GetAnimatorComponent()->SetJumpingSprite();
	
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
	GetAnimatorComponent()->SetArrivingSprite(0);
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

std::unique_ptr<qbert::CoilyState> qbert::CoilyDyingState::HandleTransitions()
{
	if (m_CurrentDyingTime >= m_MaxDyingTime) return std::make_unique<CoilyArrivingState>();
	return nullptr;
}

void qbert::CoilyDyingState::Update()
{
	m_CurrentDyingTime += dae::EngineTime::GetInstance().GetDeltaTime();

	GetDeadFallComponent()->UpdateMovement();
}

void qbert::CoilyDyingState::Enter(dae::GameObject& coilyObject)
{
	CoilyState::Enter(coilyObject);

	GetDeadFallComponent()->InitValues();
	GetMoveComponent()->SetCurrentIndex(0);

	dae::EventManager::GetInstance().CallFunction(static_cast<int>(qbert::EventType::COILYDEATH));
}
