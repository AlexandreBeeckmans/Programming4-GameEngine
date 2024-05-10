#include "QbertMoveComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "MapComponent.h"
#include "TileComponent.h"
#include "EngineTime.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"

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
	if (!m_IsWaiting) return;
	if (m_IsDead) return;

	if(direction.x > 0)
	{
		m_directionState = QbertDirection::BOTTOMRIGHT;
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
	}

	if (direction.y < 0)
	{
		m_directionState = QbertDirection::BOTTOMLEFT;
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
	}

	if (direction.x < 0)
	{
		m_directionState = QbertDirection::TOPLEFT;
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(1);
	}

	if (direction.y > 0)
	{
		m_directionState = QbertDirection::TOPRIGHT;
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(0);
	}

	auto& soundSystem{ dae::ServiceLocator::GetSoundSystem() };
	soundSystem.Play(static_cast<int>(SoundType::JUMP), 100.0f);
	m_IsWaiting = false;
	m_pMap->SetNextTile(m_directionState);
	SetMovementDirection();
}

void qbert::QbertMoveComponent::Update()
{
	if (m_IsDead) return;
	if(!m_IsWaiting)
	{
		Bounce();
		constexpr float speed{ 55.0f };

		GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
		m_AccumulatedDistanceX += speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);

		

		if (m_AccumulatedDistanceX >= m_MaxDistanceX)
		{
			m_AccumulatedDistanceX = 0;
			m_AdditionalY = 0;
			m_IsWaiting = true;
			if(m_pMap->GetCurrentTile())GetOwner()->SetLocalPosition(m_pMap->GetCurrentTile()->GetStartPoint());

			if (m_pMap)
			{
				if (m_pMap->GetCurrentTile())
				{
					m_pMap->ActivateCurrentTile();
					if(m_pMap->IsComplete())
					{
						m_IsWaiting = true;
						m_IsDead = true;
						dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::FALL), 100.0f);
					}
				}
				else
				{
					
					Kill();
				}
			}
		}
	}
}

void qbert::QbertMoveComponent::SetBubbleImage(dae::ImageComponent* pImageComponent)
{
	m_pBubbleImage = pImageComponent;
}

void qbert::QbertMoveComponent::Kill()
{
	if (m_IsDead) return;

	m_IsDead = true;
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::FALL), 100.0f);
	ShowBubble();
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
		m_CurrentIndex = m_pMap->GetCurrentIndex();

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

void qbert::QbertMoveComponent::ShowBubble() const
{
	if (!m_pBubbleImage) return;
	m_pBubbleImage->SetVisible(true);

}
