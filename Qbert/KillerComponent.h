#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"

namespace qbert
{
	class KillableComponent;
	class GridMoveComponent;

	class KillerComponent final : public dae::BaseComponent
	{
	public:
		KillerComponent(dae::GameObject* owner, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects);
		virtual ~KillerComponent() override = default;


		KillerComponent(const KillerComponent& other) = delete;
		KillerComponent(KillerComponent&& other) = delete;
		KillerComponent& operator=(const KillerComponent& other) = delete;
		KillerComponent& operator=(KillerComponent&& other) = delete;

		virtual void Init() override;

		void CheckForPlayer() const;

	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };

		std::vector<GridMoveComponent*> m_pPlayerMoveComponents{ };
		std::vector<KillableComponent*> m_pPlayerKillableComponents{ };
	};
}


