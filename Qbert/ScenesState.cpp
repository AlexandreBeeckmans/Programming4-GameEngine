#include "ScenesState.h"

#include "EngineTime.h"
#include "SceneManager.h"

void qbert::SceneStates::Exit()
{
	dae::SceneManager::GetInstance().ClearScenes();
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
}

qbert::SceneStates* qbert::LevelSceneState::HandleTransitions()
{
	if (QbertScenes::gameOver) return new StartMenuSceneState{};
	return nullptr;
}

void qbert::LevelSceneState::Enter()
{
	QbertScenes::LoadQbertLevel();
	QbertScenes::goNext = false;
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
	QbertScenes::LoadLevelLoading();
	QbertScenes::goNext = false;
}
