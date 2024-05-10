#pragma once
#include "QbertScenes.h"
#include "SceneManager.h"

namespace qbert
{
	class SceneStates
	{
	public:
		virtual ~SceneStates() {}

		virtual SceneStates* HandleTransitions() { return nullptr; }
		virtual void Update() {}
		virtual void Enter() {}
		virtual void Exit();
	};

	class StartMenuSceneState final :public SceneStates
	{
	public:

		virtual SceneStates* HandleTransitions() override;
		virtual void Enter() override;
	};

	class LevelSceneState final :public SceneStates
	{
	public:

		virtual SceneStates* HandleTransitions() override;
		//virtual void Update() override;
		virtual void Enter() override;
	};

	class LevelLoadingState final :public SceneStates
	{
	public:

		virtual SceneStates* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter() override;

	private :
		const float m_MaxWaitingTime{ 5.0f };
		float m_CurrentWaitingTime{0.0f};
	};

	
}

