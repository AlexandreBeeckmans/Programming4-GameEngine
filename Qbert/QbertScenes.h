#pragma once
#include <memory>

#include "GameObject.h"
#include "SceneCollection.h"
#include "ScenesState.h"
#include "Singleton.h"

namespace dae
{
	class ScoreComponent;
}

namespace dae
{
	class HealthComponent;
}

namespace qbert
{
	class MapComponent;

	class QbertScenes final : public dae::SceneCollection, public dae::Observer, public dae::Singleton<QbertScenes>
	{
	public:
		void Init();

		void LoadQbertLevel(const int level, const int round, const int nbPlayerLevel, const bool isVersus = false);
		void LoadStartMenu();
		void LoadLevelLoading(const int level);

		virtual void Update() override;
		std::unique_ptr<SceneStates> m_pSceneState{ std::make_unique<qbert::StartMenuSceneState>(qbert::StartMenuSceneState{}) };

		void SetNbPlayer(const int nbPlayers);
		void ReducePlayer();
		bool AreAllPlayersDead();

		void AddHealthComponents(dae::HealthComponent* pComp);
		void ClearHealthComponents();

		void AddScoreComponent(dae::ScoreComponent* pComp);
		void ClearScoreComponents();

		virtual void UpdateObserver() override;

		bool goNext{false};
		bool gameOver{false};

		std::vector<int> m_Lives{};
		std::vector<int> m_Scores{};

	private :
		const float m_LevelScale{2.0f};
		int nbPlayer{};

		std::vector<dae::HealthComponent*> m_pHealthComponents{};
		std::vector<dae::ScoreComponent*> m_pScoreComponents{};

		std::unique_ptr<dae::GameObject> CreatePlayer(const int playerNb, MapComponent* pMapComponent);
		std::unique_ptr<dae::GameObject> CreateBubble(dae::GameObject* pPlayerObject);
		std::unique_ptr<dae::GameObject> CreateCoily(const int coilyNb, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent, const bool isVersus);
		std::unique_ptr<dae::GameObject> CreateUgg(bool isLeft);
		std::unique_ptr<dae::GameObject> CreateSlick(const bool isSlick, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent);


	};
}


