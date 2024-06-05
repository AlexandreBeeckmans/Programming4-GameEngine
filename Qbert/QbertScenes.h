#pragma once
#include <memory>

#include "GameObject.h"
#include "SceneCollection.h"
#include "ScenesState.h"


namespace qbert
{
	class MapComponent;

	class QbertScenes final : public dae::SceneCollection
	{
	public:
		static void Init();

		static void LoadQbertLevel(const int level, const int round, const int nbPlayerLevel, const bool isVersus = false);
		static void LoadStartMenu();
		static void LoadLevelLoading(const int level);

		virtual void Update() override;
		static std::unique_ptr<SceneStates> m_pSceneState;

		static void SetNbPlayer(const int nbPlayers);
		static void ReducePlayer();
		static bool AreAllPlayersDead();

		static bool goNext;
		static bool gameOver;
	private :
		static const float m_LevelScale;
		static int nbPlayer;

		static std::unique_ptr<dae::GameObject> CreatePlayer(const int playerNb, MapComponent* pMapComponent);
		static std::unique_ptr<dae::GameObject> CreateBubble(dae::GameObject* pPlayerObject);
		static std::unique_ptr<dae::GameObject> CreateCoily(const int coilyNb, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent, const bool isVersus);
		static std::unique_ptr<dae::GameObject> CreateUgg(bool isLeft);
		static std::unique_ptr<dae::GameObject> CreateSlick(const bool isSlick, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent);
	};
}


