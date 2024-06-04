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

		static void LoadQbertLevel(const int level, const int round);
		static void LoadStartMenu();
		static void LoadLevelLoading(const int level);

		virtual void Update() override;
		static std::unique_ptr<SceneStates> m_pSceneState;

		static bool goNext;
		static bool gameOver;
	private :
		static const float m_LevelScale;

		static std::unique_ptr<dae::GameObject> CreatePlayer(MapComponent* pMapComponent);
		static std::unique_ptr<dae::GameObject> CreateBubble(dae::GameObject* pPlayerObject);
		static std::unique_ptr<dae::GameObject> CreateCoily(dae::GameObject* pPlayerObject, MapComponent* pMapComponent);
		static std::unique_ptr<dae::GameObject> CreateUgg(bool isLeft);
		static std::unique_ptr<dae::GameObject> CreateSlick(const bool isSlick, dae::GameObject* pPlayerObject, MapComponent* pMapComponent);
	};
}


