#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public BaseComponent, public Subject
	{
	public:

		HealthComponent(GameObject* m_pParent, const int maxLives = 3);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = default;
		HealthComponent(HealthComponent&& other) = default;
		HealthComponent& operator=(const HealthComponent& other) = default;
		HealthComponent& operator=(HealthComponent&& other) = default;

		void Init() override;
		void RemoveLive();

		int GetLivesRemaining()const { return m_CurrentLives; };
		int GetMaxLives() const { return  m_MaxLives; }

	private:
		const int m_MaxLives{ 3 };
		int m_CurrentLives{ m_MaxLives };

	};
}


