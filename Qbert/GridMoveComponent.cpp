#include "GridMoveComponent.h"

#include <glm/vec2.hpp>

#include "EngineTime.h"
#include "GameObject.h"
#include "MapComponent.h"

qbert::GridMoveComponent::GridMoveComponent(dae::GameObject* owner, MapComponent* pMap) :
BaseComponent(owner),
m_pMap(pMap)
{
	m_MaxDistanceX = static_cast<float>(m_pMap->GetTileByIndex(0)->GetWidth()) / 2.0f;
}

void qbert::GridMoveComponent::UpdateMovement()
{
	Bounce();

	GetOwner()->Translate(m_Speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
	m_AccumulatedDistanceX += m_Speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);
}


void qbert::GridMoveComponent::ResetPositionValues()
{
	m_AccumulatedDistanceX = 0;
	m_AdditionalY = 0;

	if (m_pMap->GetTileByIndex(m_CurrentIndex))
	{
		m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint();
		GetOwner()->SetLocalPosition(m_Target);
	}
		
}
void qbert::GridMoveComponent::SetCurrentIndexToTop()
{
	m_CurrentIndex = m_pMap->GetLastIndex();
	m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint();
}

void qbert::GridMoveComponent::SetCurrentIndex(int index)
{
	m_CurrentIndex = index;
	m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint();
}

void qbert::GridMoveComponent::SetMovementDirection()
{
	switch(m_CurrentGridDirection)
	{
	case GridDirection::BOTTOMLEFT:
		m_CurrentIndex = m_pMap->GetBottomLeftIndex(m_CurrentIndex);
		break;
	case GridDirection::BOTTOMRIGHT:
		m_CurrentIndex = m_pMap->GetBottomRightIndex(m_CurrentIndex);
		break;
	case GridDirection::TOPLEFT:
		m_CurrentIndex = m_pMap->GetTopLeftIndex(m_CurrentIndex);
		break;
	case GridDirection::TOPRIGHT:
		m_CurrentIndex = m_pMap->GetTopRightIndex(m_CurrentIndex);
		break;
	}

	if(m_CurrentIndex >= 0)
	{
		//m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint() - glm::vec2{ 0, GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h / 2 };
		m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint();
	}
	else
	{
		m_Target = glm::vec2{ GetWorldPosition() } + m_MaxDistanceX * GetDirectionVector(m_CurrentGridDirection);
	}

	m_Direction = glm::normalize(m_Target - glm::vec2{ GetOwner()->GetWorldPosition() });
}
bool qbert::GridMoveComponent::HasReachedFinalPosition() const
{
	return m_AccumulatedDistanceX >= m_MaxDistanceX;
}

qbert::TileComponent* qbert::GridMoveComponent::GetCurrentTile() const
{
	return m_pMap->GetTileByIndex(m_CurrentIndex);
}

qbert::GridDirection qbert::GridMoveComponent::GetGridDirection() const
{
	return m_CurrentGridDirection;
}

void qbert::GridMoveComponent::SetGridDirection(const GridDirection direction)
{
	m_CurrentGridDirection = direction;
}


void qbert::GridMoveComponent::Bounce()
{
	m_AdditionalY = m_JumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime();

	if (m_AccumulatedDistanceX > m_MaxDistanceX / 2.0f)
	{
		m_AdditionalY *= -1;
	}

	const glm::vec2 jumpDirection
	{
	0,
		-m_AdditionalY
	};

	GetOwner()->Translate(m_JumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * jumpDirection);
}

glm::vec2 qbert::GridMoveComponent::GetDirectionVector(const GridDirection direction)
{
	switch(direction)
	{
		case(GridDirection::BOTTOMLEFT):
			return glm::normalize(glm::vec2{ -0.5f, 0.75f });
		case(GridDirection::BOTTOMRIGHT):
			return glm::normalize(glm::vec2{ 0.5f, 0.75f });
		case(GridDirection::TOPLEFT):
			return glm::normalize(glm::vec2{ -0.5f, -0.75f });
		case(GridDirection::TOPRIGHT):
			return glm::normalize(glm::vec2{ 0.5f, -0.75f });
	}
	return glm::vec2{};
}
