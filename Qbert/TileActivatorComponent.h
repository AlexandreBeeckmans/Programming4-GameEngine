#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent;
}

namespace qbert
{
	class MapComponent;
	class GridMoveComponent;

	class TileActivatorComponent final : public dae::BaseComponent
	{
	public:
		TileActivatorComponent(dae::GameObject* owner, qbert::MapComponent* pMap);
		virtual ~TileActivatorComponent() override = default;


		TileActivatorComponent(const TileActivatorComponent& other) = delete;
		TileActivatorComponent(TileActivatorComponent&& other) = delete;
		TileActivatorComponent& operator=(const TileActivatorComponent& other) = delete;
		TileActivatorComponent& operator=(TileActivatorComponent&& other) = delete;

		virtual void Init() override;

		bool HasCompletedMap() const;
		void ActivateCurrentTile() const;
		void AnimateTiles() const;
		bool IsOnTeleporter() const;

		void ProcessWin()const;

	private:
		MapComponent* m_pMap{ nullptr };
		GridMoveComponent* m_pMoveComponent{ nullptr };

		dae::ScoreComponent* m_pScoreComponent{ nullptr };
	};
}


