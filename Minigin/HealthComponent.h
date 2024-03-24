#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:

		HealthComponent(GameObject* m_pParent);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = default;
		HealthComponent(HealthComponent&& other) = default;
		HealthComponent& operator=(const HealthComponent& other) = default;
		HealthComponent& operator=(HealthComponent&& other) = default;


		void RemoveLive();
		int GetLivesRemaining()const { return m_CurrentLives; };

	private:
		const int m_MaxLives{ 3 };
		int m_CurrentLives{ m_MaxLives };

	};
}


