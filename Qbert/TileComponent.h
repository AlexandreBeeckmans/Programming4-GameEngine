#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class TileComponent final : public dae::BaseComponent
	{
	public:
		TileComponent(dae::GameObject* m_pParent, const int maxStates = 1, const bool isReversible = false);
		virtual ~TileComponent() override = default;
		TileComponent(const TileComponent& other) = default;
		TileComponent(TileComponent&& other) = default;
		TileComponent& operator=(const TileComponent& other) = default;
		TileComponent& operator=(TileComponent&& other) = default;

		bool IsCompleted() const;

		void UpdateTile();
		void Deactivate();

		glm::vec2 GetStartPoint() const;
		int GetWidth() const;
		int GetHeight() const;

		void SetAnimated(const bool isAnimated);

	private:
		int m_CurrentState{ 0 };
		const int m_MaxState{ 2 };
		const bool m_IsReversible{ false };
	};
}


