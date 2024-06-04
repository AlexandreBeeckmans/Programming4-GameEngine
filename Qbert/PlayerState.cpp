#include "PlayerState.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "QbertScenes.h"

#include "QbertMoveComponent.h"
#include "GridMoveComponent.h"
#include "HealthComponent.h"

void qbert::PlayerState::Enter(dae::GameObject& qbertObject)
{
	m_pMoveComponent = qbertObject.GetComponent<GridMoveComponent>();
	m_pQbertComponent = qbertObject.GetComponent<QbertMoveComponent>();

	m_pHealthComponent = qbertObject.GetComponent<dae::HealthComponent>();
}

qbert::PlayerState* qbert::WaitingState::HandleTransitions()
{

	//If an enemy is on the same index
	if(GetQbertComponent()->IsEnemyEncounteredThisFrame())
	{
		return new DieState();
	}

	//If an input is pressed
	if (GetQbertComponent()->IsInputPressedThisFrame())
	{
		return new JumpingState{};
	}

	if(GetQbertComponent()->HasCompletedMap())
	{
		return new WinState{};
	}

	return nullptr;


}

void qbert::WaitingState::Enter(dae::GameObject& qbertObject)
{
	PlayerState::Enter(qbertObject);
	GetMoveComponent()->ResetPositionValues();
	GetQbertComponent()->ActivateCurrentTile();
}

qbert::PlayerState* qbert::JumpingState::HandleTransitions()
{
	if (!GetMoveComponent()->HasReachedFinalPosition()) return nullptr;

	if (GetMoveComponent()->GetCurrentIndex() >= 0) return new WaitingState{};

	if (GetQbertComponent()->IsOnTeleporter()) return new TeleportingState{};
	return new DieState{};
}

void qbert::JumpingState::Update()
{
	GetMoveComponent()->UpdateMovement();
}
void qbert::JumpingState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	//Set sprite
	GetQbertComponent()->SetJumpSprite();

	//Play jumpSound
	GetQbertComponent()->PlayJumpSound();

	//Set Movement direction
	GetMoveComponent()->SetMovementDirection();
}

qbert::PlayerState* qbert::DieState::HandleTransitions()
{
	if (m_CurrentDeadTime < m_MaxDeadTime) return nullptr;

	return new WaitingState{};
}

void qbert::DieState::Update()
{
	m_CurrentDeadTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::DieState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	GetQbertComponent()->Kill();
	m_CurrentDeadTime = 0;
}

void qbert::DieState::Exit()
{
	GetQbertComponent()->Respawn();
	if (GetHealthComponent()->IsDead())
	{
		QbertScenes::gameOver = true;
	}
}

qbert::PlayerState* qbert::WinState::HandleTransitions()
{
	if (m_CurrentWinTime < m_MaxWinTime) return nullptr;

	QbertScenes::goNext = true;
	return new WaitingState{};
}

void qbert::WinState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	GetQbertComponent()->PlayWinSound();
	GetQbertComponent()->AnimateTiles();
}

void qbert::WinState::Update()
{
	m_CurrentWinTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

qbert::PlayerState* qbert::TeleportingState::HandleTransitions()
{
	if (GetQbertComponent()->GetParent() != nullptr) return nullptr;

	return new FallingState{};
}

qbert::PlayerState* qbert::FallingState::HandleTransitions()
{
	if (!GetQbertComponent()->HasReachedFallPos()) return nullptr;
	return new WaitingState{};
}

void qbert::FallingState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	GetMoveComponent()->SetCurrentIndexToTop();

}

void qbert::FallingState::Update()
{
	GetQbertComponent()->UpdateFall();
}
