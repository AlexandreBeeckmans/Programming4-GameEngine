#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public BaseComponent, public Subject
	{
	public:

		HealthComponent(GameObject* m_pParent, const int livesRemaining);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = default;
		HealthComponent(HealthComponent&& other) = default;
		HealthComponent& operator=(const HealthComponent& other) = default;
		HealthComponent& operator=(HealthComponent&& other) = default;

		void RemoveLive();

		int GetLivesRemaining()const { return m_CurrentLives; }
		void SetLivesRemaining(const int livesRemaining) { m_CurrentLives = livesRemaining; }

		static int GetMaxLives() { return  m_MaxLives; }

		bool IsDead() const { return m_CurrentLives <= 0; }

	private:
		constexpr static int m_MaxLives{ 4 };
		int m_CurrentLives{ m_MaxLives };
		bool m_IsDead{ false };

	};
}


