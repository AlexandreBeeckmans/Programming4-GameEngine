#include "CoilyMoveComponent.h"

#include "EngineTime.h"
#include "MapComponent.h"

qbert::CoilyMoveComponent::CoilyMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap, QbertMoveComponent* pPlayer) :
BaseComponent(owner),
m_pMap(pMap)
{
		GetOwner()->SetLocalPosition(pMap->GetTileByIndex(0)->GetStartPoint());
		m_MaxDistanceX = static_cast<float>(m_pMap->GetCurrentTile()->GetWidth()) / 2.0f;
		m_pPlayer = pPlayer;
}

void qbert::CoilyMoveComponent::Update()
{
	if(m_IsWaiting)
	{
		UpdateWaitingTimer();
	}
	else
	{
		UpdateMovement();
	}

}

void qbert::CoilyMoveComponent::Bounce()
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

void qbert::CoilyMoveComponent::SetMovementDirection()
{
	const int playerRow = m_pMap->GetRowFromIndex(m_pPlayer->GetCurrentIndex());
	const int playerColumn = m_pMap->GetColumnFromIndex(m_pPlayer->GetCurrentIndex());

	const int coilyRow = m_pMap->GetRowFromIndex(m_CurrentIndex);
	const int coilyColumn = m_pMap->GetColumnFromIndex(m_CurrentIndex);


	if(playerRow < coilyRow)
	{
		if(playerColumn < coilyColumn)
		{
			m_CurrentIndex = m_pMap->GetBottomLeftIndex(m_CurrentIndex);
			m_Direction = { -0.5f, 0.75f };
			GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(9);
			return;
		}

		m_CurrentIndex = m_pMap->GetBottomRightIndex(m_CurrentIndex);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(7);
		m_Direction = { 0.5f, 0.75f };
		return;
	}

	if(playerColumn < coilyColumn)
	{
		m_CurrentIndex = m_pMap->GetTopLeftIndex(m_CurrentIndex);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(5);
		m_Direction = { -0.5f, -0.75f };
		return;
	}

	m_CurrentIndex = m_pMap->GetTopRightIndex(m_CurrentIndex);
	GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
	m_Direction = { 0.5f, -0.75f };
}

void qbert::CoilyMoveComponent::UpdateMovement()
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
	}
}

void qbert::CoilyMoveComponent::UpdateWaitingTimer()
{
	if(m_pPlayer->GetCurrentIndex() == m_CurrentIndex)
	{
		m_pPlayer->EncountersEnemy();
	}


	m_AccumulatedWaitingTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_AccumulatedWaitingTime >= m_MaxWaitingTime)
	{
		m_AccumulatedWaitingTime = 0;
		m_IsWaiting = false;
		SetMovementDirection();
	}
}
