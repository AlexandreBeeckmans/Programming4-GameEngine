#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent;
}

namespace qbert
{
	class BubbleManagerComponent;
	class GridMoveComponent;

	class KillableComponent final : public dae::BaseComponent
	{
	public:
		KillableComponent(dae::GameObject* owner);
		virtual ~KillableComponent() override = default;


		KillableComponent(const KillableComponent& other) = delete;
		KillableComponent(KillableComponent&& other) = delete;
		KillableComponent& operator=(const KillableComponent& other) = delete;
		KillableComponent& operator=(KillableComponent&& other) = delete;

		virtual void Init() override;
		virtual void Update() override;

		void EncountersEnemy();

		//Die State
		void Kill() const;
		void Respawn() const;


		bool IsEnemyEncounteredThisFrame()const { return m_EnemyEncounteredThisFrame; }

	private:
		bool m_EnemyEncounteredThisFrame{ false };

		BubbleManagerComponent* m_pBubbleComponent{ nullptr };
		GridMoveComponent* m_pMoveComponent{ nullptr };

		dae::HealthComponent* m_pHealthComponent{ nullptr };
	};
	
}


