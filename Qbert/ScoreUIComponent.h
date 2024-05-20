#pragma once
#include "ImageComponent.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent;
}

namespace qbert
{
	class ScoreUIComponent final : public dae::ImageComponent, public dae::Observer
	{

	public:
		ScoreUIComponent(dae::GameObject* pOwner, dae::TextComponent* pScoreText, const int playerNb);
		virtual ~ScoreUIComponent() override = default;


		ScoreUIComponent(const ScoreUIComponent& other) = delete;
		ScoreUIComponent(ScoreUIComponent&& other) = delete;
		ScoreUIComponent& operator=(const ScoreUIComponent& other) = delete;
		ScoreUIComponent& operator=(ScoreUIComponent&& other) = delete;

		virtual void UpdateObserver() override;

		void SetScoreComponent(dae::ScoreComponent* pScoreComponent);

	private:
		dae::TextComponent* m_pScoreText{ nullptr };
		dae::ScoreComponent* m_pScoreComponent{ nullptr };
	};
	
}


