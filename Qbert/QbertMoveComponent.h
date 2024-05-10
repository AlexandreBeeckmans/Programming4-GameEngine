#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "ImageComponent.h"

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
		void SetBubbleImage(dae::ImageComponent* pImageComponent);

		int GetCurrentIndex() const { return m_CurrentIndex; }
		bool IsWaiting() const { return m_IsWaiting; }

		void Kill();




	private:
		void Bounce();
		void SetMovementDirection();
		void ShowBubble() const;

		QbertDirection m_directionState{QbertDirection::TOPRIGHT};
		glm::vec2 m_Direction{0.5f,-0.75f};

		bool m_IsWaiting{ true };

		float m_MaxDistanceX{ 0.0f };
		float m_AccumulatedDistanceX{ 0.0f };

		float m_AdditionalY{ 0.0f };

		MapComponent* m_pMap{ nullptr };
		bool m_IsDead{ false };

		dae::ImageComponent* m_pBubbleImage{ nullptr };

		int m_CurrentIndex{ 0 };
	};
}


