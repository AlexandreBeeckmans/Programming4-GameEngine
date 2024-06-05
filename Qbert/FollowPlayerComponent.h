#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"


namespace qbert
{
	class GridMoveComponent;
	class MapComponent;

	class FollowPlayerComponent final : public dae::BaseComponent
	{
	public:
		FollowPlayerComponent(dae::GameObject* owner, std::vector<std::unique_ptr<dae::GameObject>>* pPlayers, MapComponent* pMap);
		virtual ~FollowPlayerComponent() override = default;


		FollowPlayerComponent(const FollowPlayerComponent& other) = delete;
		FollowPlayerComponent(FollowPlayerComponent&& other) = delete;
		FollowPlayerComponent& operator=(const FollowPlayerComponent& other) = delete;
		FollowPlayerComponent& operator=(FollowPlayerComponent&& other) = delete;

		virtual void Init() override;

		void SetMovementDirection() const;

	private:

		GridMoveComponent* m_pMoveComponent{ nullptr };

		std::vector<GridMoveComponent*> m_pPlayerMoveComponents{ };

		MapComponent* m_pMap{ nullptr };
	};
}


