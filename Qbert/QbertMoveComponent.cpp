#include "QbertMoveComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "MapComponent.h"
#include "TileComponent.h"
#include "EngineTime.h"

qbert::QbertMoveComponent::QbertMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap):
BaseComponent(owner),
m_pMap(pMap)
{
	GetOwner()->SetLocalPosition(pMap->GetCurrentTile()->GetStartPoint());
}

void qbert::QbertMoveComponent::SetDirection(const glm::vec2& direction)
{
	if (!m_IsWaiting) return;
	if (m_IsDead) return;

	if(direction.x > 0)
	{
		m_directionState = QbertDirection::BOTTOMRIGHT;
		m_Direction = { 0.5f,0.75f };
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
		return;
	}

	if (direction.y < 0)
	{
		m_directionState = QbertDirection::BOTTOMLEFT;
		m_Direction = { -0.5f,0.75f };
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		return;
	}

	if (direction.x < 0)
	{
		m_directionState = QbertDirection::TOPLEFT;
		m_Direction = { -0.5f,-0.75f };
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(1);
		return;
	}

	if (direction.y > 0)
	{
		m_directionState = QbertDirection::TOPRIGHT;
		m_Direction = { 0.5f,-0.75f };
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(0);
	}
}

void qbert::QbertMoveComponent::Update()
{
	if (m_IsDead) return;
	if(!m_IsWaiting)
	{
		Bounce();
		constexpr float speed{ 35.0f };

		GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
		m_AccumulatedDistanceX += speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);

		

		if(m_AccumulatedDistanceX >= m_MaxDistanceX)
		{
			m_AccumulatedDistanceX = 0;
			m_AdditionalY = 0;
			m_IsWaiting = true;

			if (m_pMap)
			{
				m_pMap->SetNextTile(m_directionState);

				if(m_pMap->GetCurrentTile())
				{
					m_pMap->ActivateCurrentTile();
				}
				else
				{
					m_IsDead = true;
				}
				
			}
		}
		return;
	}

	m_AccumulatedWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_AccumulatedWaitingTime >= m_WaitingTime)
	{
		m_AccumulatedWaitingTime = 0.0f;
		m_IsWaiting = false;
	}
	
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
