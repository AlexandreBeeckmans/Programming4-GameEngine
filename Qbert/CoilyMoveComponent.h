#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

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
	void SetMovementDirection();

private:


		glm::vec2 m_ArrivingTarget{};
		glm::vec2 m_ArrivingDirection{};

		QbertMoveComponent* m_pPlayer{ nullptr };
		GridMoveComponent* m_pPlayerMoveComponent{ nullptr };

		GridMoveComponent* m_pMoveComponent{ nullptr };

		CoilyState* m_State{ nullptr };

		MapComponent* m_pMap{ nullptr };
	};
}


