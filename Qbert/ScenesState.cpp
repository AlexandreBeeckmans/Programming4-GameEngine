#include "ScenesState.h"

#include "EngineTime.h"
#include "InputManager.h"
#include "QbertScenes.h"
#include "SceneManager.h"

int qbert::SceneStates::m_LevelNumber{ 0 };
int qbert::SceneStates::m_RoundNumber{ 0 };
bool qbert::SceneStates::m_LevelFinished{ false };

void qbert::SceneStates::Exit()
{
	dae::SceneManager::GetInstance().ClearScenes();
	dae::InputManager::GetInstance().UnbindAll();
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

	if (m_LevelNumber >= 3) QbertScenes::gameOver = true;
}

qbert::SceneStates* qbert::StartMenuSceneState::HandleTransitions()
{
	if (QbertScenes::goNext) return new LevelLoadingState{};
	return nullptr;
}

void qbert::StartMenuSceneState::Enter()
{
	QbertScenes::LoadStartMenu();
	QbertScenes::gameOver = false;
	ResetLevelAndRound();
}

qbert::SceneStates* qbert::LevelSceneState::HandleTransitions()
{
	if (QbertScenes::gameOver) return new StartMenuSceneState{};

	if (QbertScenes::goNext)
	{
		IncrementRound();

		if (!IsLevelFinished())
			return new LevelSceneState{};

		return new LevelLoadingState{};
	}

	return nullptr;
}



void qbert::LevelSceneState::Enter()
{
	QbertScenes::goNext = false;
	QbertScenes::LoadQbertLevel(GetLevelNumber(),GetRoundNumber());

	dae::SceneManager::GetInstance().Init();
}

void qbert::LevelSceneState::Exit()
{
	SceneStates::Exit();
	//IncrementRound();
}

qbert::SceneStates* qbert::LevelLoadingState::HandleTransitions()
{
	if (m_CurrentWaitingTime >= m_MaxWaitingTime) return new LevelSceneState{};
	return nullptr;
}

void qbert::LevelLoadingState::Update()
{
	m_CurrentWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
}

void qbert::LevelLoadingState::Enter()
{
	QbertScenes::LoadLevelLoading(GetLevelNumber());
	QbertScenes::goNext = false;
	SetLevelFinished(false);
}
