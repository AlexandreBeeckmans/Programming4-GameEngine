#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent final : public BaseComponent, public Subject
	{
	public:

		ScoreComponent(GameObject* m_pParent);
		~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = default;
		ScoreComponent(ScoreComponent&& other) = default;
		ScoreComponent& operator=(const ScoreComponent& other) = default;
		ScoreComponent& operator=(ScoreComponent&& other) = default;

		void Init() override;
		void IncrementScore(const int& valueToAdd);
		int GetScore()const { return m_CurrentScore; };

	private:
		int m_CurrentScore{ 0 };

	};
}

