#pragma once
#include <vector>

#include "BaseComponent.h"
#include "QbertMoveComponent.h"
#include "TileComponent.h"

namespace qbert
{
	class MapComponent final : public dae::BaseComponent
	{
	public:

		MapComponent(dae::GameObject* pOwner);
		virtual ~MapComponent() override = default;
		MapComponent(const MapComponent& other) = default;
		MapComponent(MapComponent&& other) = default;
		MapComponent& operator=(const MapComponent& other) = default;
		MapComponent& operator=(MapComponent&& other) = default;

		void AddTile(TileComponent* pTileComponent);
		void SetNextTile(QbertDirection direction);
		void ActivateCurrentTile() const;

		TileComponent* GetCurrentTile() const;
		void SetCurrentIndexToLast();
		bool IsComplete() const;

	private:
		std::vector<TileComponent*> m_pTiles{};
		int m_CurrentTileIndex{0};

		void SetTopLeftTile();
		void SetTopRightTile();
		void SetBottomLeft();
		void SetBottomRight();

		
	};
}


