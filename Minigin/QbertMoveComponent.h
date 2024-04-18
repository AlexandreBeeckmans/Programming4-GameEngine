#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
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
		QbertMoveComponent(dae::GameObject* owner);
		~QbertMoveComponent() = default;


		QbertMoveComponent(const QbertMoveComponent& other) = default;
		QbertMoveComponent(QbertMoveComponent&& other) = default;
		QbertMoveComponent& operator=(const QbertMoveComponent& other) = default;
		QbertMoveComponent& operator=(QbertMoveComponent&& other) = default;

		void SetDirection(const glm::vec2& direction);
	};
}


