#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "MapComponent.h"

namespace qbert
{
	enum class GridDirection
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT
	};


	class MapComponent;
	class TileComponent;

	class GridMoveComponent final : public dae::BaseComponent
	{
	public:
		GridMoveComponent(dae::GameObject* owner, MapComponent* pMap);
		virtual ~GridMoveComponent() override = default;


		GridMoveComponent(const GridMoveComponent& other) = delete;
		GridMoveComponent(GridMoveComponent&& other) = delete;
		GridMoveComponent& operator=(const GridMoveComponent& other) = delete;
		GridMoveComponent& operator=(GridMoveComponent&& other) = delete;

		

		void UpdateMovement();
		void ResetPositionValues();

		void SetCurrentIndexToTop();
		void SetMovementDirection();

		bool HasReachedFinalPosition() const;

		int GetCurrentIndex() const { return m_CurrentIndex; }
		const TileComponent* GetCurrentTile() const;

		GridDirection GetGridDirection() const;
		void SetGridDirection(const GridDirection direction);

	private:

		const float m_Speed{ 100.0f };
		const float m_JumpSpeed{ 75.0f };

		float m_AccumulatedDistanceX{ 0.0f };
		float m_MaxDistanceX{ 0.0f };

		float m_AdditionalY{ 0.0f };

		glm::vec2 m_Direction{ 0.0f,0.0f };
		GridDirection m_CurrentGridDirection{};

		glm::vec2 m_Target{};

		int m_CurrentIndex{};

		MapComponent* m_pMap{ nullptr };


		void Bounce();
		static glm::vec2 GetDirectionVector(const GridDirection direction);
	};
}


