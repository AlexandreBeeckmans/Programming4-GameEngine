#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "CoilyState.h"

namespace qbert
{
	class KillableComponent;
}

namespace qbert
{
	class CoilyState;
	class GridMoveComponent;
	class MapComponent;
	class QbertMoveComponent;
	//class GameObject;

	class CoilyMoveComponent final : public dae::BaseComponent
	{
	public:
	CoilyMoveComponent(dae::GameObject* owner, dae::GameObject* pPlayerObject, MapComponent* pMap);
	virtual ~CoilyMoveComponent() override = default;


	CoilyMoveComponent(const CoilyMoveComponent& other) = delete;
	CoilyMoveComponent(CoilyMoveComponent&& other) = delete;
	CoilyMoveComponent& operator=(const CoilyMoveComponent& other) = delete;
	CoilyMoveComponent& operator=(CoilyMoveComponent&& other) = delete;

		void Update() override;
		void Init() override;

		void CheckForPlayer() const;
		void UpdateArrivingMovement() const;

		bool IsArrived() const;


		void SetWaitingSprite() const;
		void SetArrivingSprite(const int column) const;

		void SetVisible() const;
		void SetMovementDirection() const;

private:


		glm::vec2 m_ArrivingTarget{};
		glm::vec2 m_ArrivingDirection{};

		GridMoveComponent* m_pPlayerMoveComponent{ nullptr };
		KillableComponent* m_pPlayerKillableComponent{ nullptr };

		GridMoveComponent* m_pMoveComponent{ nullptr };

		std::unique_ptr<CoilyState> m_State{ nullptr };

		MapComponent* m_pMap{ nullptr };
	};
}


