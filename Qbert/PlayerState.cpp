#include "PlayerState.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "QbertScenes.h"

#include "QbertMoveComponent.h"
#include "GridMoveComponent.h"
#include "FallComponent.h"
#include "InputDirectionComponent.h"
#include "KillableComponent.h"
#include "TileActivatorComponent.h"
#include "QbertJumpAnimatorComponent.h"

#include "HealthComponent.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"


void qbert::PlayerState::Enter(dae::GameObject& qbertObject)
{
	m_pMoveComponent = qbertObject.GetComponent<GridMoveComponent>();
	m_pQbertComponent = qbertObject.GetComponent<QbertMoveComponent>();
	m_pFallComponent = qbertObject.GetComponent<FallComponent>();
	m_pInputComponent = qbertObject.GetComponent<InputDirectionComponent>();
	m_pKillableComponent = qbertObject.GetComponent<KillableComponent>();
	m_pTileActivatorComponent = qbertObject.GetComponent<TileActivatorComponent>();
	m_pJumpAnimator = qbertObject.GetComponent<QbertJumpAnimatorComponent>();

	m_pHealthComponent = qbertObject.GetComponent<dae::HealthComponent>();
}

qbert::PlayerState* qbert::WaitingState::HandleTransitions()
{

	//If an enemy is on the same index
	if(GetKillableComponent()->IsEnemyEncounteredThisFrame())
	{
		return new DieState();
	}

	//If an input is pressed
	if (GetInputComponent()->IsInputPressedThisFrame())
	{
		return new JumpingState{};
	}

	if(GetTileActivatorComponent()->HasCompletedMap())
	{
		return new WinState{};
	}

	return nullptr;


}

void qbert::WaitingState::Enter(dae::GameObject& qbertObject)
{
	PlayerState::Enter(qbertObject);
	GetMoveComponent()->ResetPositionValues();

}

qbert::PlayerState* qbert::JumpingState::HandleTransitions()
{
	if (!GetMoveComponent()->HasReachedFinalPosition()) return nullptr;

	if (GetMoveComponent()->GetCurrentIndex() >= 0) return new WaitingState{};

	if (GetTileActivatorComponent()->IsOnTeleporter()) return new TeleportingState{};
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
	GetJumpAnimator()->SetJumpSprite();

	//Play jumpSound
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::JUMP), 100.0f);

	//Set Movement direction
	GetMoveComponent()->SetMovementDirection();
}

void qbert::JumpingState::Exit()
{
	GetTileActivatorComponent()->ActivateCurrentTile();
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
	GetKillableComponent()->Kill();
	m_CurrentDeadTime = 0;
}

void qbert::DieState::Exit()
{
	GetKillableComponent()->Respawn();
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
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::WIN), 100.0f);
	GetTileActivatorComponent()->AnimateTiles();
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
	if (!GetFallComponent()->HasReachedFallPos()) return nullptr;
	return new WaitingState{};
}

void qbert::FallingState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	GetMoveComponent()->SetCurrentIndexToTop();
	GetFallComponent()->SetFallDirection();

}

void qbert::FallingState::Update()
{
	GetFallComponent()->UpdateFall();
}
