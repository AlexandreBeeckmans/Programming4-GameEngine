#pragma once
#include <vector>

#include "BaseComponent.h"

namespace dae
{
	class ImageComponent;
}

namespace qbert
{
	class ChangeToUIComponent final : public dae::BaseComponent
	{

	public:
		ChangeToUIComponent(dae::GameObject* pOwner, const std::vector<dae::ImageComponent*>& arrows);
		virtual ~ChangeToUIComponent() override = default;


		ChangeToUIComponent(const ChangeToUIComponent& other) = delete;
		ChangeToUIComponent(ChangeToUIComponent&& other) = delete;
		ChangeToUIComponent& operator=(const ChangeToUIComponent& other) = delete;
		ChangeToUIComponent& operator=(ChangeToUIComponent&& other) = delete;

		virtual void Update() override;


	private:
		std::vector<dae::ImageComponent*> m_Arrows;
		float m_AccumulatedTime{ 0 };
		const float m_BlinkTime{ 0.5f };

		int m_CurrentStep{ 0 };
		const int m_Steps{ 0 };
	};

}
