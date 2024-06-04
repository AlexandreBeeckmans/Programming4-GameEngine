#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;
}

namespace qbert
{
	class MapComponent;
	class TileDeactivatorComponent final : public dae::BaseComponent
	{
	public:
		TileDeactivatorComponent(dae::GameObject* owner, MapComponent* pMap);
		virtual ~TileDeactivatorComponent() override = default;


		TileDeactivatorComponent(const TileDeactivatorComponent& other) = delete;
		TileDeactivatorComponent(TileDeactivatorComponent&& other) = delete;
		TileDeactivatorComponent& operator=(const TileDeactivatorComponent& other) = delete;
		TileDeactivatorComponent& operator=(TileDeactivatorComponent&& other) = delete;

		virtual void Init() override;

		void DeactivateCurrentTile() const;

	private:
		MapComponent* m_pMap{ nullptr };
		GridMoveComponent* m_pMoveComponent{ nullptr };
	};
}


