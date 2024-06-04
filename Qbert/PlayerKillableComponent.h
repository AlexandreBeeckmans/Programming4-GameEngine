#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class KillableComponent;
	class GridMoveComponent;

	class PlayerKillableComponent final : public dae::BaseComponent
	{
	public:
		PlayerKillableComponent(dae::GameObject* owner, GridMoveComponent* pPlayerMoveComponent);
		virtual ~PlayerKillableComponent() override = default;


		PlayerKillableComponent(const PlayerKillableComponent& other) = delete;
		PlayerKillableComponent(PlayerKillableComponent&& other) = delete;
		PlayerKillableComponent& operator=(const PlayerKillableComponent& other) = delete;
		PlayerKillableComponent& operator=(PlayerKillableComponent&& other) = delete;

		virtual void Init() override;
		bool IsEncounteringPlayer() const;

	private:

		GridMoveComponent* m_pMoveComponent{ nullptr };

		GridMoveComponent* m_pPlayerMoveComponent{ nullptr };
	};
}


