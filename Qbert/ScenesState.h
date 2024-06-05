#pragma once
#include <memory>

namespace qbert
{
	enum class GameMode
	{
		SOLO,
		COOP,
		VERSUS
	};

	class SceneStates
	{
	public:
		virtual ~SceneStates() {}

		virtual std::unique_ptr<SceneStates> HandleTransitions() { return nullptr; }
		virtual void Update() {}
		virtual void Enter() {}
		virtual void Exit();

		static bool IncrementGameMode(const int addedValue);

	protected:
		static void ResetLevelAndRound();
		static void IncrementRound();

		static int GetLevelNumber() { return m_LevelNumber; }
		static int GetRoundNumber() { return m_RoundNumber; }
		static bool IsLevelFinished() { return m_LevelFinished; }
		static void SetLevelFinished(const bool isFinished) { m_LevelFinished = isFinished; }

		static GameMode m_GameMode;

	private:
		static int m_LevelNumber;
		static int m_RoundNumber;
		static bool m_LevelFinished;
	};

	class StartMenuSceneState final :public SceneStates
	{
	public:

		virtual std::unique_ptr<SceneStates> HandleTransitions() override;
		virtual void Enter() override;
	};

	class LevelSceneState final :public SceneStates
	{
	public:

		virtual std::unique_ptr<SceneStates> HandleTransitions() override;
		virtual void Enter() override;
		virtual void Exit() override;
	};

	class LevelLoadingState final :public SceneStates
	{
	public:

		virtual std::unique_ptr<SceneStates> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter() override;

	private :
		const float m_MaxWaitingTime{ 3.0f };
		float m_CurrentWaitingTime{0.0f};
	};

	
}

