#include "ScenesState.h"

#include "EngineTime.h"
#include "EventManager.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "QbertCommand.h"
#include "QbertScenes.h"
#include "SceneManager.h"

int qbert::SceneStates::m_LevelNumber{ 0 };
int qbert::SceneStates::m_RoundNumber{ 0 };
bool qbert::SceneStates::m_LevelFinished{ false };
qbert::GameMode qbert::SceneStates::m_GameMode{ qbert::GameMode::SOLO };

void qbert::SceneStates::Enter()
{
	dae::MuteCommand muteCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_F2, std::make_unique<dae::MuteCommand>(muteCommand), dae::InputType::DOWN);
}

void qbert::SceneStates::Exit()
{
	dae::SceneManager::GetInstance().ClearScenes();
	dae::InputManager::GetInstance().UnbindAll();
}

bool qbert::SceneStates::IncrementGameMode(const int addedValue)
{
	if (static_cast<int>(m_GameMode) + addedValue >= 3) return false;
	if (static_cast<int>(m_GameMode) + addedValue < 0) return false;

	m_GameMode = static_cast<GameMode>(static_cast<int>(m_GameMode) + addedValue);
	return true;
}

void qbert::SceneStates::ResetLevelAndRound()
{
	m_LevelNumber = 0;
	m_RoundNumber = 0;
}

void qbert::SceneStates::IncrementRound()
{
	++m_RoundNumber;

	if(m_RoundNumber >= 6)
	{
		++m_LevelNumber;
		m_RoundNumber = 0;
		SetLevelFinished(true);
	}

	if (m_LevelNumber >= 3) QbertScenes::GetInstance().gameOver = true;
}

void qbert::SceneStates::IncrementLevel()
{
	m_RoundNumber = 0;
	++m_LevelNumber;

	if(m_LevelNumber >= 3)
	{
		m_LevelNumber = 0;
	}
}

std::unique_ptr<qbert::SceneStates> qbert::StartMenuSceneState::HandleTransitions()
{
	if (QbertScenes::GetInstance().goNext) return std::make_unique<LevelLoadingState>(LevelLoadingState{});
	return nullptr;
}

void qbert::StartMenuSceneState::Enter()
{
	SceneStates::Enter();

	QbertScenes::GetInstance().LoadStartMenu();
	QbertScenes::GetInstance().gameOver = false;
	QbertScenes::GetInstance().m_Lives.clear();
	QbertScenes::GetInstance().m_Scores.clear();
	QbertScenes::GetInstance().goNext = false;
	m_GameMode = GameMode::SOLO;

	ResetLevelAndRound();
	
}

void qbert::StartMenuSceneState::Exit()
{
	SceneStates::Exit();

	QbertScenes::GetInstance().m_Lives.push_back(dae::HealthComponent::GetMaxLives());
	QbertScenes::GetInstance().m_Scores.push_back(0);
	if (m_GameMode == GameMode::COOP)
	{
		QbertScenes::GetInstance().m_Lives.push_back(dae::HealthComponent::GetMaxLives());
		QbertScenes::GetInstance().m_Scores.push_back(0);
	}
}

std::unique_ptr<qbert::SceneStates> qbert::LevelSceneState::HandleTransitions()
{
	if (QbertScenes::GetInstance().gameOver) return std::make_unique<GameOverScreen>();

	if (QbertScenes::GetInstance().goNext)
	{
		IncrementRound();

		if (!IsLevelFinished())
			return std::make_unique<LevelSceneState>(LevelSceneState{});


		if (QbertScenes::GetInstance().gameOver) return std::make_unique<GameOverScreen>();
		return std::make_unique<LevelLoadingState>(LevelLoadingState{});
	}

	if(QbertScenes::GetInstance().skipLevel)
	{
		QbertScenes::GetInstance().skipLevel = false;
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
	SceneStates::Enter();

	SkipLevelCommand skipLevelCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_F1, std::make_unique<qbert::SkipLevelCommand>(skipLevelCommand), dae::InputType::DOWN);



	QbertScenes::GetInstance().goNext = false;

	switch(m_GameMode)
	{
	case(GameMode::SOLO):
		QbertScenes::GetInstance().LoadQbertLevel(GetLevelNumber(), GetRoundNumber(), 1);
		break;
	case(GameMode::COOP):
		QbertScenes::GetInstance().LoadQbertLevel(GetLevelNumber(), GetRoundNumber(), 2);
		break;
	case(GameMode::VERSUS):
		QbertScenes::GetInstance().LoadQbertLevel(GetLevelNumber(), GetRoundNumber(), 1, true);
		break;
	}
	

	dae::SceneManager::GetInstance().Init();
}

void qbert::LevelSceneState::Exit()
{
	SceneStates::Exit();
	QbertScenes::GetInstance().ClearHealthComponents();
	QbertScenes::GetInstance().ClearScoreComponents();
	dae::EventManager::GetInstance().ClearFunctions();
}

std::unique_ptr<qbert::SceneStates> qbert::LevelLoadingState::HandleTransitions()
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
	SceneStates::Enter();

	QbertScenes::GetInstance().LoadLevelLoading(GetLevelNumber());
	QbertScenes::GetInstance().goNext = false;
	SetLevelFinished(false);
}

std::unique_ptr<qbert::SceneStates> qbert::GameOverScreen::HandleTransitions()
{
	if (QbertScenes::GetInstance().goNext) return std::make_unique<StartMenuSceneState>();
	return nullptr;
}

void qbert::GameOverScreen::Enter()
{
	SceneStates::Enter();

	QbertScenes::GetInstance().LoadGameOverScreen();
	dae::SceneManager::GetInstance().Init();
}

void qbert::GameOverScreen::Exit()
{
	SceneStates::Exit();
	QbertScenes::GetInstance().LeaveGameOverScreen();
}
