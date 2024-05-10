#pragma once
#include "GameObject.h"
#include "QbertMoveComponent.h"

namespace qbert
{
	class MapComponent;

	class CoilyMoveComponent final : public dae::BaseComponent
	{
	public:
		CoilyMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap, QbertMoveComponent* pPlayer);
		virtual ~CoilyMoveComponent() override = default;


		CoilyMoveComponent(const CoilyMoveComponent& other) = delete;
		CoilyMoveComponent(CoilyMoveComponent&& other) = delete;
		CoilyMoveComponent& operator=(const CoilyMoveComponent& other) = delete;
		CoilyMoveComponent& operator=(CoilyMoveComponent&& other) = delete;

		void Update() override;

	private:

		void Bounce();
		void SetMovementDirection();

		void UpdateMovement();
		void UpdateWaitingTimer();


		glm::vec2 m_Direction{ 0.5f,-0.75f };

		bool m_IsWaiting{ true };

		float m_MaxDistanceX{ 0.0f };
		float m_AccumulatedDistanceX{ 0.0f };

		float m_AdditionalY{ 0.0f };

		MapComponent* m_pMap{ nullptr };
		QbertMoveComponent* m_pPlayer{ nullptr };

		float m_AccumulatedWaitingTime{ 0.0f };
		const float m_MaxWaitingTime{ 2.0f };

		int m_CurrentIndex{ 0 };
	};
}


