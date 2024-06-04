#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class DeadFallComponent final : public dae::BaseComponent
	{
	public:
		DeadFallComponent(dae::GameObject* owner);
		virtual ~DeadFallComponent() override = default;


		DeadFallComponent(const DeadFallComponent& other) = delete;
		DeadFallComponent(DeadFallComponent&& other) = delete;
		DeadFallComponent& operator=(const DeadFallComponent& other) = delete;
		DeadFallComponent& operator=(DeadFallComponent&& other) = delete;

		void InitValues();
		void UpdateMovement();

		bool IsOutOfMap() const;

	private:

		static constexpr float m_StartVerticalSpeed{ 100.0f };
		static constexpr float m_Gravity{ -98.1f };

		float m_VerticalSpeed{ 0.0f };

	};
}


