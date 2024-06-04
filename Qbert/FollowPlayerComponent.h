#pragma once
#include "BaseComponent.h"


namespace qbert
{
	class GridMoveComponent;
	class MapComponent;

	class FollowPlayerComponent final : public dae::BaseComponent
	{
	public:
		FollowPlayerComponent(dae::GameObject* owner, GridMoveComponent* pPlayerMovement, MapComponent* pMap);
		virtual ~FollowPlayerComponent() override = default;


		FollowPlayerComponent(const FollowPlayerComponent& other) = delete;
		FollowPlayerComponent(FollowPlayerComponent&& other) = delete;
		FollowPlayerComponent& operator=(const FollowPlayerComponent& other) = delete;
		FollowPlayerComponent& operator=(FollowPlayerComponent&& other) = delete;

		virtual void Init() override;

		void SetMovementDirection() const;

	private:

		GridMoveComponent* m_pMoveComponent{ nullptr };
		GridMoveComponent* m_pPlayerMoveComponent{ nullptr };
		MapComponent* m_pMap{ nullptr };
	};
}


