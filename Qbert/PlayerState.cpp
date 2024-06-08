#include "PlayerState.h"

#include "EngineTime.h"
#include "EventManager.h"
#include "EventTypes.h"
#include "GameObject.h"
#include "QbertScenes.h"

#include "GridMoveComponent.h"
#include "FallComponent.h"
#include "InputDirectionComponent.h"
#include "KillableComponent.h"
#include "TileActivatorComponent.h"
#include "QbertJumpAnimatorComponent.h"
#include "ScoreComponent.h"

#include "HealthComponent.h"
#include "QbertGameState.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"


void qbert::PlayerState::Enter(dae::GameObject& qbertObject)
{
	m_pMoveComponent = qbertObject.GetComponent<GridMoveComponent>();
	m_pFallComponent = qbertObject.GetComponent<FallComponent>();
	m_pInputComponent = qbertObject.GetComponent<InputDirectionComponent>();
	m_pKillableComponent = qbertObject.GetComponent<KillableComponent>();
	m_pTileActivatorComponent = qbertObject.GetComponent<TileActivatorComponent>();
	m_pJumpAnimator = qbertObject.GetComponent<QbertJumpAnimatorComponent>();

	m_pHealthComponent = qbertObject.GetComponent<dae::HealthComponent>();
	m_pImageComponent = qbertObject.GetComponent<dae::ImageComponent>();
	m_pScoreComponent = qbertObject.GetComponent<dae::ScoreComponent>();
}

std::unique_ptr<qbert::PlayerState> qbert::WaitingState::HandleTransitions()
{

	//If an enemy is on the same index
	if(GetKillableComponent()->IsEnemyEncounteredThisFrame())
	{
		dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::HIT), 100.0f);
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

	if (GetHealthComponent()->IsDead())
	{

		return std::make_unique<DeadState>();
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

	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::FALL), 100.0f);
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
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::JUMP), 100.0f);

	//Set Movement direction
	GetMoveComponent()->SetMovementDirection();
}

void qbert::JumpingState::Exit()
{
	GetTileActivatorComponent()->ActivateCurrentTile();
}

std::unique_ptr<qbert::PlayerState> qbert::DieState::HandleTransitions()
{
	if (m_CurrentDeadTime < m_MaxDeadTime) return nullptr;
	if (GetHealthComponent()->IsDead()) return std::make_unique<DeadState>();

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
	m_CurrentDeadTime = 0;

	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::SWEAR), 100.0f);
}

void qbert::DieState::Exit()
{
	GetKillableComponent()->Respawn();
}


bool qbert::WinState::m_HasWon{ false };
std::unique_ptr<qbert::PlayerState> qbert::WinState::HandleTransitions()
{
	
	if (m_CurrentWinTime < m_MaxWinTime) return nullptr;
	QbertScenes::GetInstance().goNext = true;
	m_HasWon = false;
	
	return std::make_unique<WaitingState>();
}

void qbert::WinState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	

	if(!m_HasWon)
	{
		dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::WIN), 100.0f);
		GetTileActivatorComponent()->AnimateTiles();
		m_HasWon = true;
	}

	GetTileActivatorComponent()->ProcessWin();
		
	
}

void qbert::WinState::Update()
{
	m_CurrentWinTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

std::unique_ptr<qbert::PlayerState> qbert::TeleportingState::HandleTransitions()
{
	if (GetMoveComponent()->GetParent() != nullptr) return nullptr;

	return std::make_unique<FallingState>();
}

void qbert::TeleportingState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::DISKMOVE), 100.0f);
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
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::DISKLAND), 100.0f);

}

void qbert::FallingState::Update()
{
	GetFallComponent()->UpdateFall();
}

void qbert::DeadState::Enter(dae::GameObject& qbert)
{
	PlayerState::Enter(qbert);
	QbertGameState::GetInstance().ReducePlayer();
	if (QbertGameState::GetInstance().AreAllPlayersDead())
	{
		QbertScenes::GetInstance().gameOver = true;
	}

	
	GetImageComponent()->SetVisible(false);
	GetImageComponent()->SetOwnerActive(false);
}
