#pragma once
#include <memory>

#include "GameObject.h"
#include "SceneCollection.h"
#include "ScenesState.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
}

namespace qbert
{
	

	class MapComponent;

	class QbertScenes final : public dae::SceneCollection, public dae::Singleton<QbertScenes>
	{
	public:
		void Init();
		void LeaveGameOverScreen();

		virtual void Update() override;
		std::unique_ptr<SceneState> m_pSceneState{ std::make_unique<qbert::StartMenuSceneState>() };


		void LoadSounds();

		bool goNext{false};
		bool gameOver{false};
		bool skipLevel{ false };

		std::unique_ptr<dae::GameObject> CreatePlayer(const int playerNb, MapComponent* pMapComponent);
		std::unique_ptr<dae::GameObject> CreateBubble(dae::GameObject* pPlayerObject);
		std::unique_ptr<dae::GameObject> CreateCoily(const int coilyNb, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent, const bool isVersus);
		std::unique_ptr<dae::GameObject> CreateUgg(bool isLeft, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent);
		std::unique_ptr<dae::GameObject> CreateSlick(const bool isSlick, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent);


		void CreateGameUI(dae::Scene* pScene, const std::vector<std::unique_ptr<dae::GameObject>>& playerObjects, const int level, const int round);
		void CreateScoreUIObject(dae::Scene* pScene, const std::unique_ptr<dae::GameObject>& pPlayerObject, const int playerNb);
		void CreateNextTileUIObject(dae::Scene* pScene, const int level, const int round);
		void CreateControlsUIObject(dae::Scene* pScene);
		void CreateDiscObject(dae::Scene* pScene, MapComponent* pMapComponent, const bool isLeft, const int round);
	};
}


