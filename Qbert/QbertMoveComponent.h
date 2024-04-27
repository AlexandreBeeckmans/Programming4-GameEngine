#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class MapComponent;
	enum class QbertDirection
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT
	};
	class QbertMoveComponent final : public dae::BaseComponent
	{
	public:
		QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap);
		virtual ~QbertMoveComponent() override = default;


		QbertMoveComponent(const QbertMoveComponent& other) = delete;
		QbertMoveComponent(QbertMoveComponent&& other) = delete;
		QbertMoveComponent& operator=(const QbertMoveComponent& other) = delete;
		QbertMoveComponent& operator=(QbertMoveComponent&& other) = delete;

		void SetDirection(const glm::vec2& direction);
		void Update() override;




	private:
		void Bounce();
		void SetMovementDirection();

		QbertDirection m_directionState{QbertDirection::TOPRIGHT};
		glm::vec2 m_Direction{0.5f,-0.75f};

		bool m_IsWaiting{ true };

		float m_MaxDistanceX{ 0.0f };
		float m_AccumulatedDistanceX{ 0.0f };

		float m_AdditionalY{ 0.0f };

		MapComponent* m_pMap{ nullptr };
		bool m_IsDead{ false };
	};
}


