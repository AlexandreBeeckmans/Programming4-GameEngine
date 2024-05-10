#include "QbertMoveComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "MapComponent.h"
#include "TileComponent.h"
#include "EngineTime.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"
#include "PlayerState.h"

qbert::QbertMoveComponent::QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap):
BaseComponent(owner),
m_pMap(pMap)
{
	GetOwner()->SetLocalPosition(pMap->GetCurrentTile()->GetStartPoint());
	m_MaxDistanceX = static_cast<float>(m_pMap->GetCurrentTile()->GetWidth())/2.0f;
	m_CurrentIndex = m_pMap->GetCurrentIndex();
}

void qbert::QbertMoveComponent::SetDirection(const glm::vec2& direction)
{
	m_IsInputPressedThisFrame = true;

	if(direction.x > 0)
	{
		m_directionState = QbertDirection::BOTTOMRIGHT;
	}

	if (direction.y < 0)
	{
		m_directionState = QbertDirection::BOTTOMLEFT;
	}

	if (direction.x < 0)
	{
		m_directionState = QbertDirection::TOPLEFT;
	}

	if (direction.y > 0)
	{
		m_directionState = QbertDirection::TOPRIGHT;
	}
}

void qbert::QbertMoveComponent::Update()
{
	PlayerState* newState = m_PlayerState->HandleTransitions(*this);
	if(newState)
	{
		m_PlayerState->Exit(*this);
		delete m_PlayerState;
		m_PlayerState = newState;
		m_PlayerState->Enter(*this);
	}

	m_PlayerState->Update(*this);

	m_IsInputPressedThisFrame = false;
	m_EnemyEncounteredThisFrame = false;
}

void qbert::QbertMoveComponent::Init()
{
	m_PlayerState = new WaitingState{};
}

void qbert::QbertMoveComponent::SetBubbleImage(dae::ImageComponent* pImageComponent)
{
	m_pBubbleImage = pImageComponent;
}

void qbert::QbertMoveComponent::Kill() const
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::FALL), 100.0f);
	ShowBubble(true);
}

void qbert::QbertMoveComponent::Respawn()
{
	m_pMap->SetCurrentIndexToLast();
	m_CurrentIndex = m_pMap->GetCurrentIndex();
	GetOwner()->SetLocalPosition(m_pMap->GetCurrentTile()->GetStartPoint());
	ShowBubble(false);
}

void qbert::QbertMoveComponent::PlayWinSound()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::WIN), 100.0f);
}


void qbert::QbertMoveComponent::EncountersEnemy()
{
	m_EnemyEncounteredThisFrame = true;
}

bool qbert::QbertMoveComponent::HasCompletedMap() const
{
	return m_pMap->IsComplete();
}

//Jump state
void qbert::QbertMoveComponent::UpdateMovement()
{
	Bounce();
	constexpr float speed{ 55.0f };

	GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
	m_AccumulatedDistanceX += speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);
}
void qbert::QbertMoveComponent::SetJumpSprite() const
{
	switch(m_directionState)
	{
	case(QbertDirection::BOTTOMRIGHT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
		break;

	case(QbertDirection::BOTTOMLEFT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		break;

	case(QbertDirection::TOPRIGHT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(0);
		break;

	case(QbertDirection::TOPLEFT) :
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(1);
		break;
	}
}
void qbert::QbertMoveComponent::PlayJumpSound()
{
	auto& soundSystem{ dae::ServiceLocator::GetSoundSystem() };
	soundSystem.Play(static_cast<int>(SoundType::JUMP), 100.0f);
}
void qbert::QbertMoveComponent::SetJumpDirection()
{
	m_pMap->SetNextTile(m_directionState);
	m_CurrentIndex = m_pMap->GetCurrentIndex();
	SetMovementDirection();
}
void qbert::QbertMoveComponent::ResetPositionValues()
{
	m_AccumulatedDistanceX = 0;
	m_AdditionalY = 0;

	if(m_pMap->GetCurrentTile())
		GetOwner()->SetLocalPosition(m_pMap->GetCurrentTile()->GetStartPoint());


}
bool qbert::QbertMoveComponent::HasReachedFinalPosition() const
{
	return m_AccumulatedDistanceX >= m_MaxDistanceX;
}
void qbert::QbertMoveComponent::ActivateCurrentTile() const
{
	if (!m_pMap->GetCurrentTile()) return;
	m_pMap->ActivateCurrentTile();
}

void qbert::QbertMoveComponent::Bounce()
{
	constexpr float jumpSpeed{ 50.0f };
	m_AdditionalY = jumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime();

	if (m_AccumulatedDistanceX > m_MaxDistanceX / 2.0f)
	{
		m_AdditionalY *= -1;
	}

	const glm::vec2 jumpDirection
	{
	0,
		-m_AdditionalY
	};

	GetOwner()->Translate(jumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * jumpDirection);

}
void qbert::QbertMoveComponent::SetMovementDirection()
{
	if (m_pMap->GetCurrentTile())
	{
		const glm::vec2 target{ m_pMap->GetCurrentTile()->GetStartPoint() };
		const glm::vec2 from{ GetOwner()->GetWorldPosition() };

		m_Direction = normalize(target - from);
		return;
	}

	switch(m_directionState)
	{
	case QbertDirection::TOPRIGHT:
	{
		m_Direction = { 0.5f, -0.75f };
		break;
	}
	case QbertDirection::TOPLEFT:
	{
		m_Direction = { -0.5f, -0.75f };
		break;
	}
	case QbertDirection::BOTTOMRIGHT:
	{
		m_Direction = { 0.5f, 0.75f };
		break;
	}
	case QbertDirection::BOTTOMLEFT:
	{
		m_Direction = { -0.5f, 0.75f };
		break;
	}

	}
	
}
void qbert::QbertMoveComponent::ShowBubble(const bool showBubble) const
{
	if (!m_pBubbleImage) return;


	m_pBubbleImage->SetVisible(showBubble);

}
