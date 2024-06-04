#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class KillableComponent;
	class GridMoveComponent;

	class KillerComponent final : public dae::BaseComponent
	{
	public:
		KillerComponent(dae::GameObject* owner, dae::GameObject* pPlayerObject);
		virtual ~KillerComponent() override = default;


		KillerComponent(const KillerComponent& other) = delete;
		KillerComponent(KillerComponent&& other) = delete;
		KillerComponent& operator=(const KillerComponent& other) = delete;
		KillerComponent& operator=(KillerComponent&& other) = delete;

		virtual void Init() override;

		void CheckForPlayer() const;

	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };

		GridMoveComponent* m_pPlayerMoveComponent{ nullptr };
		KillableComponent* m_pPlayerKillableComponent{ nullptr };
	};
}


