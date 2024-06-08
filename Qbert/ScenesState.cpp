#include "ScenesState.h"

#include "EngineTime.h"
#include "EventManager.h"
#include "GameOverLevel.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "LoadLevel.h"
#include "MainLevel.h"
#include "QbertCommand.h"
#include "QbertGameState.h"
#include "QbertScenes.h"
#include "SceneManager.h"
#include "StartMenuLevel.h"

int qbert::SceneState::m_LevelNumber{ 0 };
int qbert::SceneState::m_RoundNumber{ 0 };
bool qbert::SceneState::m_LevelFinished{ false };
qbert::GameMode qbert::SceneState::m_GameMode{ qbert::GameMode::SOLO };

void qbert::SceneState::Enter()
{

	QbertScenes::GetInstance().SetGoNextScene(false);
	
	dae::MuteCommand muteCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_F2, std::make_unique<dae::MuteCommand>(muteCommand), dae::InputType::DOWN);
	dae::SceneManager::GetInstance().Init();
	if(m_AssociatedLevel)
	{
		m_AssociatedLevel->Load();
	}
	dae::SceneManager::GetInstance().Init();
}

void qbert::SceneState::Exit()
{
	dae::SceneManager::GetInstance().ClearScenes();
	dae::InputManager::GetInstance().UnbindAll();
}

bool qbert::SceneState::IncrementGameMode(const int addedValue)
{
	if (static_cast<int>(m_GameMode) + addedValue >= 3) return false;
	if (static_cast<int>(m_GameMode) + addedValue < 0) return false;

	m_GameMode = static_cast<GameMode>(static_cast<int>(m_GameMode) + addedValue);
	return true;
}

void qbert::SceneState::ResetLevelAndRound()
{
	m_LevelNumber = 0;
	m_RoundNumber = 0;
}

void qbert::SceneState::IncrementRound()
{
	++m_RoundNumber;

	if(m_RoundNumber >= 6)
	{
		++m_LevelNumber;
		m_RoundNumber = 0;
		SetLevelFinished(true);
	}

	if (m_LevelNumber >= 3) QbertScenes::GetInstance().SetGameOver(true);
}

void qbert::SceneState::IncrementLevel()
{
	m_RoundNumber = 0;
	++m_LevelNumber;

	if(m_LevelNumber >= 3)
	{
		m_LevelNumber = 0;
	}
}

void qbert::SceneState::SetGameMode(const GameMode& gameMode)
{
	m_GameMode = gameMode;
}

qbert::StartMenuSceneState::StartMenuSceneState()
{
	m_AssociatedLevel = std::make_unique<StartMenuLevel>();
}

std::unique_ptr<qbert::SceneState> qbert::StartMenuSceneState::HandleTransitions()
{
	if (QbertScenes::GetInstance().IsGoingNext()) return std::make_unique<LevelLoadingState>(LevelLoadingState{});
	return nullptr;
}

void qbert::StartMenuSceneState::Enter()
{
	SceneState::Enter();

	QbertScenes::GetInstance().SetGameOver(false);
	QbertGameState::GetInstance().ClearLives();
	QbertGameState::GetInstance().ClearScores();
	QbertScenes::GetInstance().SetGoNextScene(false);
	SetGameMode(GameMode::SOLO);

	ResetLevelAndRound();
	
}

void qbert::StartMenuSceneState::Exit()
{
	SceneState::Exit();

	QbertGameState::GetInstance().AddLive(dae::HealthComponent::GetMaxLives());
	QbertGameState::GetInstance().AddScore(0);
	if (GetGameMode() == GameMode::COOP)
	{
		QbertGameState::GetInstance().AddLive(dae::HealthComponent::GetMaxLives());
		QbertGameState::GetInstance().AddScore(0);
	}
}

std::unique_ptr<qbert::SceneState> qbert::LevelSceneState::HandleTransitions()
{
	if (QbertScenes::GetInstance().IsGameOver()) return std::make_unique<GameOverScreen>();

	if (QbertScenes::GetInstance().IsGoingNext())
	{
		IncrementRound();

		if (!IsLevelFinished())
			return std::make_unique<LevelSceneState>(LevelSceneState{});


		if (QbertScenes::GetInstance().IsGameOver()) return std::make_unique<GameOverScreen>();
		return std::make_unique<LevelLoadingState>(LevelLoadingState{});
	}

	if(QbertScenes::GetInstance().IsSkippingLevel())
	{
		QbertScenes::GetInstance().SetSkipLevel(false);
		IncrementLevel();

		if(GetLevelNumber() > 0)
		{
			return std::make_unique<LevelLoadingState>(LevelLoadingState{});
		}
		return std::make_unique<GameOverScreen>();
		
		
	}

	return nullptr;
}



void qbert::LevelSceneState::Enter()
{
	switch (GetGameMode())
	{
	case(GameMode::SOLO):
		m_AssociatedLevel = std::make_unique<MainLevel>(GetLevelNumber(), GetRoundNumber(), 1, false);
		break;
	case(GameMode::COOP):
		m_AssociatedLevel = std::make_unique<MainLevel>(GetLevelNumber(), GetRoundNumber(), 2, false);
		break;
	case(GameMode::VERSUS):
		m_AssociatedLevel = std::make_unique<MainLevel>(GetLevelNumber(), GetRoundNumber(), 1, true);
		break;
	}
	SceneState::Enter();

	SkipLevelCommand skipLevelCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_F1, std::make_unique<qbert::SkipLevelCommand>(skipLevelCommand), dae::InputType::DOWN);



	QbertScenes::GetInstance().SetGoNextScene(false);

	
	

	
}

void qbert::LevelSceneState::Exit()
{
	SceneState::Exit();
	QbertGameState::GetInstance().ClearHealthComponents();
	QbertGameState::GetInstance().ClearScoreComponents();
	dae::EventManager::GetInstance().ClearFunctions();
}

qbert::LevelLoadingState::LevelLoadingState()
{
	m_AssociatedLevel = std::make_unique<LoadLevel>(GetLevelNumber());
}

std::unique_ptr<qbert::SceneState> qbert::LevelLoadingState::HandleTransitions()
{
	if (m_CurrentWaitingTime >= m_MaxWaitingTime) return std::make_unique<LevelSceneState>(LevelSceneState{});
	return nullptr;
}

void qbert::LevelLoadingState::Update()
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::LevelLoadingState::Enter()
{
	SceneState::Enter();

	
	SetLevelFinished(false);
}

qbert::GameOverScreen::GameOverScreen()
{
	m_AssociatedLevel = std::make_unique<GameOverLevel>();
}

std::unique_ptr<qbert::SceneState> qbert::GameOverScreen::HandleTransitions()
{
	if (QbertScenes::GetInstance().IsGoingNext()) return std::make_unique<StartMenuSceneState>();
	return nullptr;
}

void qbert::GameOverScreen::Enter()
{
	SceneState::Enter();
}

void qbert::GameOverScreen::Exit()
{
	SceneState::Exit();
	QbertScenes::GetInstance().LeaveGameOverScreen();
}
