#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;
	class InputDirectionComponent final : public dae::BaseComponent
	{
	public:
		InputDirectionComponent(dae::GameObject* owner);
		virtual ~InputDirectionComponent() override = default;


		InputDirectionComponent(const InputDirectionComponent& other) = delete;
		InputDirectionComponent(InputDirectionComponent&& other) = delete;
		InputDirectionComponent& operator=(const InputDirectionComponent& other) = delete;
		InputDirectionComponent& operator=(InputDirectionComponent&& other) = delete;

		virtual void Init() override;
		virtual void Update() override;

		virtual void SetInputDirection(const glm::vec2& direction);

		bool IsInputPressedThisFrame()const { return m_IsInputPressedThisFrame; }

	private:
		bool m_IsInputPressedThisFrame{ false };
		GridMoveComponent* m_pMoveComponent{ nullptr };

	};
}


