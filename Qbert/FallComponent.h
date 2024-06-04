#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;

	class FallComponent final : public dae::BaseComponent
	{
	public:
		FallComponent(dae::GameObject* owner);
		virtual ~FallComponent() override = default;

		FallComponent(const FallComponent& other) = delete;
		FallComponent(FallComponent&& other) = delete;
		FallComponent& operator=(const FallComponent& other) = delete;
		FallComponent& operator=(FallComponent&& other) = delete;

		virtual void Init() override;

		void SetFallDirection();
		void UpdateFall();
		bool HasReachedFallPos() const;

	private:
		glm::vec2 m_FallDirection{};
		glm::vec2 m_FallTarget{};

		static constexpr float m_FallSpeed{ 100.0f };

		float m_AccumulatedDistanceToFall{ 0.0f };
		float m_MaxDistanceToFall{ 0.0f };

		GridMoveComponent* m_pMoveComponent{ nullptr };
	};
}


