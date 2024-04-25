#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class TileComponent final : public dae::BaseComponent
	{
	public:
		TileComponent(dae::GameObject* m_pParent);
		virtual ~TileComponent() override = default;
		TileComponent(const TileComponent& other) = default;
		TileComponent(TileComponent&& other) = default;
		TileComponent& operator=(const TileComponent& other) = default;
		TileComponent& operator=(TileComponent&& other) = default;

		bool IsCompleted() const;
		void UpdateTile();

		glm::vec2 GetStartPoint() const;
		int GetWidth() const;

	private:
		int m_CurrentState{ 0 };
		const int m_MaxState{ 2 };
	};
}


