#include "QbertGameState.h"

#include <json.hpp>
#include <fstream>

#include "HealthComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

void qbert::QbertGameState::SetNbPlayer(const int nbPlayers)
{
	m_NbPlayer = nbPlayers;
}

void qbert::QbertGameState::ReducePlayer()
{
	--m_NbPlayer;
}

bool qbert::QbertGameState::AreAllPlayersDead()
{
	return m_NbPlayer <= 0;
}

void qbert::QbertGameState::AddHealthComponents(dae::HealthComponent* pComp)
{
	m_pHealthComponents.push_back(pComp);
}

void qbert::QbertGameState::ClearHealthComponents()
{
	m_pHealthComponents.clear();
}

void qbert::QbertGameState::AddScoreComponent(dae::ScoreComponent* pComp)
{
	m_pScoreComponents.push_back(pComp);
}

void qbert::QbertGameState::ClearScoreComponents()
{
	m_pScoreComponents.clear();
}

void qbert::QbertGameState::UpdateObserver()
{
	for (size_t i{ 0 }; i < m_pHealthComponents.size(); ++i)
	{
		m_Lives[i] = m_pHealthComponents[i]->GetLivesRemaining();
	}

	for (size_t i{ 0 }; i < m_pScoreComponents.size(); ++i)
	{
		m_Scores[i] = m_pScoreComponents[i]->GetScore();
	}
}

void qbert::QbertGameState::AddScore(const int newScore)
{
	m_Scores.push_back(newScore);
}

int qbert::QbertGameState::GetScoreAtIndex(const int index)
{
	return m_Scores[index];
}

void qbert::QbertGameState::ClearScores()
{
	m_Scores.clear();
}

void qbert::QbertGameState::AddLive(const int newLive)
{
	m_Lives.push_back(newLive);
}

int qbert::QbertGameState::GetLiveAtIndex(const int index)
{
	return m_Lives[index];
}

void qbert::QbertGameState::ClearLives()
{
	m_Lives.clear();
}

int qbert::QbertGameState::GetScoreSum() const
{
	return std::accumulate(std::cbegin(m_Scores), std::cend(m_Scores), 0);
}

qbert::ScoreData qbert::QbertGameState::GetHighScore()
{
	nlohmann::json json = dae::ResourceManager::GetInstance().ReadFile("../Data/qbert/highscore.json");
	ScoreData currentHighScore{};
	if (json.contains("name")) currentHighScore.name = json["name"];
	if (json.contains("score")) currentHighScore.score = json["score"];

	return currentHighScore;
}

void qbert::QbertGameState::TestNewScore()
{
	ScoreData highScore = GetHighScore();

	if (m_Score.score > highScore.score)
	{
		RegisterHighScore(m_Score);
	}
}

void qbert::QbertGameState::SetScore(const int newScore)
{
	m_Score.score = newScore;
}

void qbert::QbertGameState::RegisterHighScore(ScoreData newHighScore)
{
	nlohmann::json jsonObject{};

	jsonObject["name"] = newHighScore.name;
	jsonObject["score"] = newHighScore.score;

	std::ofstream file("../Data/qbert/highscore.json", std::ios::out);
	if (file.is_open())
	{
		file << jsonObject.dump(4);
		file.close();
	}
}
