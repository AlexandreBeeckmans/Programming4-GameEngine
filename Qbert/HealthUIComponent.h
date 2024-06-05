#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthComponent;
	class ImageComponent;
}

namespace qbert
{
	class HealthUIComponent final : public dae::BaseComponent, public dae::Observer
	{

	public:
		HealthUIComponent(dae::GameObject* pOwner, dae::ImageComponent* pImage);
		virtual ~HealthUIComponent() override = default;


		HealthUIComponent(const HealthUIComponent& other) = delete;
		HealthUIComponent(HealthUIComponent&& other) = delete;
		HealthUIComponent& operator=(const HealthUIComponent& other) = delete;
		HealthUIComponent& operator=(HealthUIComponent&& other) = delete;

		virtual void Init() override;

		virtual void UpdateObserver() override;

		void SetHealthComponent(dae::HealthComponent* pScoreComponent);

	private:
		dae::ImageComponent* m_pLivesImage{ nullptr };
		dae::HealthComponent* m_pHealthComponent{ nullptr };
	};

}
