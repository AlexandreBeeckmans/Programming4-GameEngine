#include "PlayerState.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "QbertScenes.h"

#include "QbertFSMManagerComponent.h"
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
	m_pQbertComponent = qbertObject.GetComponent<QbertFSMManagerComponent>();
	m_pFallComponent = qbertObject.GetComponent<FallComponent>();
	m_pInputComponent = qbertObject.GetComponent<InputDirectionComponent>();
	m_pKillableComponent = qbertObject.GetComponent<KillableComponent>();
	m_pTileActivatorComponent = qbertObject.GetComponent<TileActivatorComponent>();
	m_pJumpAnimator = qbertObject.GetComponent<QbertJumpAnimatorComponent>();

	m_pHealthComponent = qbertObject.GetComponent<dae::HealthComponent>();
}

std::unique_ptr<qbert::PlayerState> qbert::WaitingState::HandleTransitions()
{

	//If an enemy is on the same index
	if(GetKillableComponent()->IsEnemyEncounteredThisFrame())
	{
		return std::make_unique<DieState>();
	}

	//If an input is pressed
	if (GetInputComponent()->IsInputPressedThisFrame())
	{
		return std::make_unique<JumpingState>();
	}

	if(GetTileActivatorComponent()->HasCompletedMap())
	{
		return std::make_unique<WinState>();
	}

	return nullptr;


}

void qbert::WaitingState::Enter(dae::GameObject& qbertObject)
{
	PlayerState::Enter(qbertObject);
	GetMoveComponent()->ResetPositionValues();

}

std::unique_ptr<qbert::PlayerState> qbert::JumpingState::HandleTransitions()
{
	if (!GetMoveComponent()->HasReachedFinalPosition()) return nullptr;

	if (GetMoveComponent()->GetCurrentIndex() >= 0) return std::make_unique<WaitingState>();

	if (GetTileActivatorComponent()->IsOnTeleporter()) return std::make_unique<TeleportingState>();
	return std::make_unique<DieState>();
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

std::unique_ptr<qbert::PlayerState> qbert::DieState::HandleTransitions()
{
	if (m_CurrentDeadTime < m_MaxDeadTime || GetHealthComponent()->IsDead()) return nullptr;

	return std::make_unique<WaitingState>();
}

void qbert::DieState::Update()
{
	m_CurrentDeadTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::DieState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	GetKillableComponent()->Kill();
	if (GetHealthComponent()->IsDead())
	{
		QbertScenes::ReducePlayer();
		if (QbertScenes::AreAllPlayersDead())
		{
			QbertScenes::gameOver = true;
		}
	}
	m_CurrentDeadTime = 0;
}

void qbert::DieState::Exit()
{
	GetKillableComponent()->Respawn();
}

std::unique_ptr<qbert::PlayerState> qbert::WinState::HandleTransitions()
{
	if (m_CurrentWinTime < m_MaxWinTime) return nullptr;

	QbertScenes::goNext = true;
	return std::make_unique<WaitingState>();
}

void qbert::WinState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	if(!QbertScenes::goNext)
		dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::WIN), 100.0f);
	GetTileActivatorComponent()->AnimateTiles();
}

void qbert::WinState::Update()
{
	m_CurrentWinTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

std::unique_ptr<qbert::PlayerState> qbert::TeleportingState::HandleTransitions()
{
	if (GetQbertComponent()->GetParent() != nullptr) return nullptr;

	return std::make_unique<FallingState>();
}

std::unique_ptr<qbert::PlayerState> qbert::FallingState::HandleTransitions()
{
	if (!GetFallComponent()->HasReachedFallPos()) return nullptr;
	return std::make_unique<WaitingState>();
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
