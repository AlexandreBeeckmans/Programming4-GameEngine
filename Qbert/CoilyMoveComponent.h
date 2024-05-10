#pragma once
#include "GameObject.h"
#include "QbertMoveComponent.h"

namespace qbert
{
	class CoilyState;
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
		void Init() override;


		void UpdateMovement();
		void CheckForPlayer() const;
		void UpdateArrivingMovement() const;

		bool HasReachedFinalPosition() const;
		bool IsArrived() const;

		void ResetPositionValues();
		void SetMovementDirection();

		void SetWaitingSprite() const;
		void SetArrivingSprite(const int column) const;

		void SetVisible() const;

	private:

		void Bounce();

		glm::vec2 m_Direction{ 0.5f,-0.75f };

		float m_MaxDistanceX{ 0.0f };
		float m_AccumulatedDistanceX{ 0.0f };

		float m_AdditionalY{ 0.0f };

		MapComponent* m_pMap{ nullptr };
		QbertMoveComponent* m_pPlayer{ nullptr };

		int m_CurrentIndex{ 0 };

		CoilyState* m_State{ nullptr };
	};
}


