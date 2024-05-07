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

		MapComponent(dae::GameObject* pOwner, const int rows);
		virtual ~MapComponent() override = default;
		MapComponent(const MapComponent& other) = default;
		MapComponent(MapComponent&& other) = default;
		MapComponent& operator=(const MapComponent& other) = default;
		MapComponent& operator=(MapComponent&& other) = default;

		void AddTile(TileComponent* pTileComponent);
		void SetNextTile(QbertDirection direction);
		void ActivateCurrentTile() const;

		TileComponent* GetCurrentTile() const;
		TileComponent* GetTileByIndex(const int index) const;

		int GetRowFromIndex(const int index) const;
		int GetColumnFromIndex(const int index) const;



		void SetCurrentIndexToLast();
		bool IsComplete() const;

		int GetTopRightIndex(const int currentIndex) const;
		int GetTopLeftIndex(const int currentIndex) const;
		int GetBottomLeftIndex(const int currentIndex) const;
		int GetBottomRightIndex(const int currentIndex) const;


	private:
		std::vector<TileComponent*> m_pTiles{};
		int m_CurrentTileIndex{0};
		const int m_Rows{ 0 };

		void SetTopLeftTile();
		void SetTopRightTile();
		void SetBottomLeft();
		void SetBottomRight();

		int GetFirstIndexOfTheRow(const int row) const;

		
	};
}


