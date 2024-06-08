#pragma once
#include <memory>

#include "Level.h"
#include "Singleton.h"
#include "State.hpp"

namespace qbert
{
	enum class GameMode
	{
		SOLO,
		COOP,
		VERSUS
	};

	class SceneState : public dae::State<SceneState>
	{
	public:
		virtual void Enter() override;
		virtual void Exit() override;

		static bool IncrementGameMode(const int addedValue);
		static GameMode GetGameMode(){ return m_GameMode; }

	protected:
		static void ResetLevelAndRound();
		static void IncrementRound();
		static void IncrementLevel();

		static int GetLevelNumber() { return m_LevelNumber; }
		static int GetRoundNumber() { return m_RoundNumber; }
		static bool IsLevelFinished() { return m_LevelFinished; }
		static void SetLevelFinished(const bool isFinished) { m_LevelFinished = isFinished; }

		static void SetGameMode(const GameMode& gameMode);

		std::unique_ptr<dae::Level> m_AssociatedLevel;

	private:
		static int m_LevelNumber;
		static int m_RoundNumber;
		static bool m_LevelFinished;
		static GameMode m_GameMode;

		
	};

	class StartMenuSceneState final :public SceneState
	{
	public:
		StartMenuSceneState();
		virtual std::unique_ptr<SceneState> HandleTransitions() override;
		virtual void Enter() override;
		virtual void Exit() override;
	};

	class LevelSceneState final :public SceneState
	{
	public:

		virtual std::unique_ptr<SceneState> HandleTransitions() override;
		virtual void Enter() override;
		virtual void Exit() override;
	};

	class LevelLoadingState final :public SceneState
	{
	public:
		LevelLoadingState();
		virtual std::unique_ptr<SceneState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter() override;

	private :
		static constexpr float m_MaxWaitingTime{ 3.0f };
		float m_CurrentWaitingTime{0.0f};
	};

	class GameOverScreen final : public SceneState
	{
	public:
		GameOverScreen();
		virtual std::unique_ptr<SceneState> HandleTransitions() override;
		virtual void Enter() override;
		virtual void Exit() override;

	private:
	};

	
}

