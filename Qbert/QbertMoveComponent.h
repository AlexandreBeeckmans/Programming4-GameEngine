#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "ImageComponent.h"
//#include "PlayerState.h"

namespace qbert
{
	class PlayerState;
	class MapComponent;
	enum class QbertDirection
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT
	};
	class QbertMoveComponent final : public dae::BaseComponent
	{
	public:
		QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap);
		virtual ~QbertMoveComponent() override = default;


		QbertMoveComponent(const QbertMoveComponent& other) = delete;
		QbertMoveComponent(QbertMoveComponent&& other) = delete;
		QbertMoveComponent& operator=(const QbertMoveComponent& other) = delete;
		QbertMoveComponent& operator=(QbertMoveComponent&& other) = delete;

		virtual void Update() override;


		
		

		//Setters
		void SetDirection(const glm::vec2& direction);
		void SetBubbleImage(dae::ImageComponent* pImageComponent);
		void SetCurrentIndexToTop();


		//Getters
		int GetCurrentIndex() const { return m_CurrentIndex; }
		bool IsInputPressedThisFrame()const { return m_IsInputPressedThisFrame; }
		bool IsEnemyEncounteredThisFrame()const { return m_EnemyEncounteredThisFrame; }

		//Waiting state
		void EncountersEnemy();
		bool HasCompletedMap() const;


		//Jump state
		void UpdateMovement();
		void SetJumpSprite() const;
		static void PlayJumpSound();
		void SetJumpDirection();
		void ResetPositionValues();
		bool HasReachedFinalPosition() const;
		void ActivateCurrentTile() const;

		//Die State
		void Kill();
		void Respawn();
		int GetLives() { return m_Lives; }

		//Win State
		static void PlayWinSound();
		void AnimateTiles();

		bool IsOnTeleporter() const;

		//Faling State
		void UpdateFall();
		bool HasReachedFallPos() const;



	private:
		void Bounce();
		void SetMovementDirection();
		void ShowBubble(const bool showBubble) const;

		const float m_Speed{ 125.0f };

		QbertDirection m_directionState{QbertDirection::TOPRIGHT};
		glm::vec2 m_Direction{0.5f,-0.75f};


		float m_MaxDistanceX{ 0.0f };
		float m_AccumulatedDistanceX{ 0.0f };
		float m_AdditionalY{ 0.0f };

		MapComponent* m_pMap{ nullptr };

		dae::ImageComponent* m_pBubbleImage{ nullptr };

		int m_CurrentIndex{ 0 };

		PlayerState* m_PlayerState{ nullptr };


		bool m_IsInputPressedThisFrame{ false };
		bool m_EnemyEncounteredThisFrame{ false };

		int m_Lives{ 3 };
	};
}


