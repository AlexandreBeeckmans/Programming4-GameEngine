#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class BlinkingComponent final : public dae::BaseComponent
	{
	public:
		BlinkingComponent(dae::GameObject* m_pOwner, const float blinkingTime = 1.0f, const bool isDefaultActivated = true);
		virtual ~BlinkingComponent() override = default;

		BlinkingComponent(const BlinkingComponent& other) = delete;
		BlinkingComponent(BlinkingComponent&& other) = delete;
		BlinkingComponent& operator=(const BlinkingComponent& other) = delete;
		BlinkingComponent& operator=(BlinkingComponent&& other) = delete;

		virtual void Update() override;

		void SetActive(const bool isActive);


	private:
		bool m_IsActive{ true };
		float m_AccumulatedTime{ 0.0f };
		float m_MaxBlinkingTime{ 1.0f };
	};
}


