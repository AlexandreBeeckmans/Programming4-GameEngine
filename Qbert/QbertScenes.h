#pragma once
#include <memory>

#include "SceneCollection.h"
#include "ScenesState.h"


namespace qbert
{
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
	};
}


