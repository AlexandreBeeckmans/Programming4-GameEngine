#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace qbert
{
	class ScoreUIComponent;
}

namespace dae
{
	class ScoreComponent final : public BaseComponent, public Subject
	{
	public:

		ScoreComponent(GameObject* m_pParent, int score = 0);
		~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = default;
		ScoreComponent(ScoreComponent&& other) = default;
		ScoreComponent& operator=(const ScoreComponent& other) = default;
		ScoreComponent& operator=(ScoreComponent&& other) = default;

		void InitObserver(qbert::ScoreUIComponent* pUiComponent);
		void IncrementScore(int scoreToAdd);
		int GetScore()const { return m_CurrentScore; };

	private:
		int m_CurrentScore{ 0 };

	};
}

