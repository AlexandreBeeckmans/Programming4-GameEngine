#include "QbertMoveComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "MapComponent.h"
#include "TileComponent.h"
#include "EngineTime.h"
#include "GridMoveComponent.h"
#include "HealthComponent.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"
#include "PlayerState.h"
#include "QbertScenes.h"
#include "ScoreComponent.h"

qbert::QbertMoveComponent::QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap):
BaseComponent(owner),
m_pMap(pMap)
{
	//m_CurrentIndex = m_pMap->GetCurrentIndex();
	m_PlayerState = new WaitingState{};
}

void qbert::QbertMoveComponent::SetDirection(const glm::vec2& direction)
{
	m_IsInputPressedThisFrame = true;

	if(direction.x > 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMRIGHT);
	}

	if (direction.y < 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMLEFT);
	}

	if (direction.x < 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPLEFT);
	}

	if (direction.y > 0)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPRIGHT);
	}
}

void qbert::QbertMoveComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
	GetOwner()->SetLocalPosition(m_pMoveComponent->GetCurrentTile()->GetStartPoint());
	m_PlayerState->Enter(*GetOwner());
}

void qbert::QbertMoveComponent::Update()
{
	PlayerState* newState = m_PlayerState->HandleTransitions();
	if(newState)
	{
		m_PlayerState->Exit();
		delete m_PlayerState;
		m_PlayerState = newState;
		m_PlayerState->Enter(*GetOwner());
	}

	m_PlayerState->Update();

	m_IsInputPressedThisFrame = false;
	m_EnemyEncounteredThisFrame = false;
}

void qbert::QbertMoveComponent::SetBubbleImage(dae::ImageComponent* pImageComponent)
{
	m_pBubbleImage = pImageComponent;
}



void qbert::QbertMoveComponent::Kill()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::FALL), 100.0f);
	ShowBubble(true);

	GetOwner()->GetComponent<dae::HealthComponent>()->RemoveLive();
}

void qbert::QbertMoveComponent::Respawn()
{
	m_pMoveComponent->SetCurrentIndexToTop();
	GetOwner()->SetLocalPosition(m_pMoveComponent->GetCurrentTile()->GetStartPoint());
	ShowBubble(false);
}

void qbert::QbertMoveComponent::PlayWinSound()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::WIN), 100.0f);
}

void qbert::QbertMoveComponent::AnimateTiles()
{
	m_pMap->SetAllTileAnimated(true);
}

bool qbert::QbertMoveComponent::IsOnTeleporter() const
{
	return m_pMap->IsOnATeleporter(this);
}

void qbert::QbertMoveComponent::UpdateFall()
{
	const glm::vec2 direction{ glm::normalize(m_pMoveComponent->GetCurrentTile()->GetStartPoint() - glm::vec2{GetWorldPosition().x, GetWorldPosition().y}) };
	/*GetOwner()->Translate(direction * m_Speed * dae::EngineTime::GetInstance().GetDeltaTime());*/
	GetOwner()->Translate(direction * 100.0f * dae::EngineTime::GetInstance().GetDeltaTime());
}

bool qbert::QbertMoveComponent::HasReachedFallPos() const
{
	return glm::length(m_pMoveComponent->GetCurrentTile()->GetStartPoint() - glm::vec2{ GetWorldPosition().x, GetWorldPosition().y }) <= 1.0f;
}


void qbert::QbertMoveComponent::EncountersEnemy()
{
	m_EnemyEncounteredThisFrame = true;
}

bool qbert::QbertMoveComponent::HasCompletedMap() const
{
	return m_pMap->IsComplete();
}

void qbert::QbertMoveComponent::SetJumpSprite() const
{
	switch(m_pMoveComponent->GetGridDirection())
	{
	case(GridDirection::BOTTOMRIGHT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
		break;

	case(GridDirection::BOTTOMLEFT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		break;

	case(GridDirection::TOPRIGHT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(0);
		break;

	case(GridDirection::TOPLEFT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(1);
		break;
	}
}
void qbert::QbertMoveComponent::PlayJumpSound()
{
	auto& soundSystem{ dae::ServiceLocator::GetSoundSystem() };
	soundSystem.Play(static_cast<int>(SoundType::JUMP), 100.0f);
}
//void qbert::QbertMoveComponent::SetJumpDirection()
//{
//	//m_pMap->SetNextTile(m_directionState);
//	//m_CurrentIndex = m_pMap->GetCurrentIndex();
//	//SetMovementDirection();
//}
//void qbert::QbertMoveComponent::ResetPositionValues()
//{
//	m_AccumulatedDistanceX = 0;
//	m_AdditionalY = 0;
//
//	if(m_pMap->GetCurrentTile())
//		GetOwner()->SetLocalPosition(m_pMap->GetCurrentTile()->GetStartPoint());
//
//
//}
//bool qbert::QbertMoveComponent::HasReachedFinalPosition() const
//{
//	return m_AccumulatedDistanceX >= m_MaxDistanceX;
//}
void qbert::QbertMoveComponent::ActivateCurrentTile() const
{
	if (!m_pMoveComponent->GetCurrentTile()) return;
	m_pMap->ActivateTileAtIndex(m_pMoveComponent->GetCurrentIndex());

	GetOwner()->GetComponent<dae::ScoreComponent>()->IncrementScore(25);
}

//void qbert::QbertMoveComponent::SetMovementDirection()
//{
//	if (m_pMap->GetCurrentTile())
//	{
//		const glm::vec2 target{ m_pMap->GetCurrentTile()->GetStartPoint() };
//		const glm::vec2 from{ GetOwner()->GetWorldPosition() };
//
//		//m_Direction = normalize(target - from);
//		return;
//	}
//}
void qbert::QbertMoveComponent::ShowBubble(const bool showBubble) const
{
	if (!m_pBubbleImage) return;


	m_pBubbleImage->SetVisible(showBubble);

}
