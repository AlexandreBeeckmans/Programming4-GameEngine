#pragma once
#include <string>
#include <vector>

#include "GameState.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent;
	class HealthComponent;
}

namespace qbert
{
	struct ScoreData
	{
		std::string name;
		int score;
	};

	class QbertGameState final : public dae::GameState, public dae::Singleton<QbertGameState>
	{
	public:
		void SetNbPlayer(const int nbPlayers);
		void ReducePlayer();
		bool AreAllPlayersDead();

		void AddHealthComponents(dae::HealthComponent* pComp);
		void ClearHealthComponents();

		void AddScoreComponent(dae::ScoreComponent* pComp);
		void ClearScoreComponents();
		void SetName(const std::string& newName) { m_Score.name = newName; }

		virtual void UpdateObserver() override;

		void AddScore(const int newScore);
		int GetScoreAtIndex(const int index);
		void ClearScores();

		void AddLive(const int newLive);
		int GetLiveAtIndex(const int index);
		void ClearLives();

		int GetScoreSum() const;

		float GetScale() const { return m_LevelScale; }

		ScoreData GetHighScore();
		void TestNewScore();
		void SetScore(const int newScore);
		

	private:
		std::vector<int> m_Lives{};
		std::vector<int> m_Scores{};

		static constexpr float m_LevelScale{ 2.0f };
		int m_NbPlayer{};
		ScoreData m_Score
		{
			"Robert",
			0
		};


		std::vector<dae::HealthComponent*> m_pHealthComponents{};
		std::vector<dae::ScoreComponent*> m_pScoreComponents{};
		void RegisterHighScore(ScoreData newHighScore);
		
		
	};
}


