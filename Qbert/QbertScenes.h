#pragma once
#include "SceneCollection.h"


namespace qbert
{
	class SceneStates;
	class QbertScenes final : public dae::SceneCollection
	{
	public:
		static void Init();

		static void LoadQbertLevel(const int level, const int round);
		static void LoadStartMenu();
		static void LoadLevelLoading();

		virtual void Update() override;
		static SceneStates* m_pSceneState;

		static bool goNext;
		static bool gameOver;
	private :
		static const float m_LevelScale;
	};
}


