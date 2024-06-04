#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "GridMoveComponent.h"
#include "ImageComponent.h"
//#include "PlayerState.h"

namespace qbert
{
	class GridMoveComponent;
}

namespace qbert
{
	class PlayerState;
	class MapComponent;

	class QbertMoveComponent final : public dae::BaseComponent
	{
	public:
		QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap);
		virtual ~QbertMoveComponent() override = default;


		QbertMoveComponent(const QbertMoveComponent& other) = delete;
		QbertMoveComponent(QbertMoveComponent&& other) = delete;
		QbertMoveComponent& operator=(const QbertMoveComponent& other) = delete;
		QbertMoveComponent& operator=(QbertMoveComponent&& other) = delete;

		virtual void Init() override;
		virtual void Update() override;


		//Setters
		void SetDirection(const glm::vec2& direction);
		void SetBubbleImage(dae::ImageComponent* pImageComponent);



		//Getters
		bool IsInputPressedThisFrame()const { return m_IsInputPressedThisFrame; }
		bool IsEnemyEncounteredThisFrame()const { return m_EnemyEncounteredThisFrame; }

		//Waiting state
		void EncountersEnemy();
		bool HasCompletedMap() const;


		//Jump state
		void SetJumpSprite() const;
		static void PlayJumpSound();
		void ActivateCurrentTile() const;

		//Die State
		void Kill();
		void Respawn();

		//Win State
		static void PlayWinSound();
		void AnimateTiles();

		bool IsOnTeleporter() const;

		//Faling State
		void UpdateFall();
		bool HasReachedFallPos() const;



	private:
		void ShowBubble(const bool showBubble) const;


		GridMoveComponent* m_pMoveComponent{ nullptr };


		MapComponent* m_pMap{ nullptr };

		dae::ImageComponent* m_pBubbleImage{ nullptr };


		PlayerState* m_PlayerState{ nullptr };


		bool m_IsInputPressedThisFrame{ false };
		bool m_EnemyEncounteredThisFrame{ false };
	};
}


