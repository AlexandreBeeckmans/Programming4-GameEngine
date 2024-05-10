#include "PlayerState.h"

#include "EngineTime.h"
#include "QbertScenes.h"

qbert::PlayerState* qbert::WaitingState::HandleTransitions(const QbertMoveComponent& qbert)
{
	//If an enemy is on the same index
	if(qbert.IsEnemyEncounteredThisFrame())
	{
		return new DieState();
	}

	//If an input is pressed
	if (qbert.IsInputPressedThisFrame())
	{
		return new JumpingState{};
	}

	if(qbert.HasCompletedMap())
	{
		return new WinState{};
	}

	return nullptr;


}

void qbert::WaitingState::Enter(QbertMoveComponent& qbert)
{
	qbert.ResetPositionValues();
	qbert.ActivateCurrentTile();
}

qbert::PlayerState* qbert::JumpingState::HandleTransitions(const QbertMoveComponent& qbert)
{
	if (!qbert.HasReachedFinalPosition()) return nullptr;

	if (qbert.GetCurrentIndex() >= 0) return new WaitingState{};

	return new DieState{};
}

void qbert::JumpingState::Update(QbertMoveComponent& qbert)
{
	qbert.UpdateMovement();
}
void qbert::JumpingState::Enter(QbertMoveComponent& qbert)
{
	//Set sprite
	qbert.SetJumpSprite();

	//Play jumpSound
	qbert.PlayJumpSound();

	//Set Movement direction
	qbert.SetJumpDirection();
}

qbert::PlayerState* qbert::DieState::HandleTransitions(const QbertMoveComponent&)
{
	if (m_CurrentDeadTime < m_MaxDeadTime) return nullptr;

	return new WaitingState{};
}

void qbert::DieState::Update(QbertMoveComponent&)
{
	m_CurrentDeadTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::DieState::Enter(QbertMoveComponent& qbert)
{
	qbert.Kill();
	m_CurrentDeadTime = 0;
}

void qbert::DieState::Exit(QbertMoveComponent& qbert)
{
	qbert.Respawn();
	if (qbert.GetLives() < 0)
	{
		QbertScenes::gameOver = true;
	}
}

void qbert::WinState::Enter(QbertMoveComponent& qbert)
{
	qbert.PlayWinSound();
}