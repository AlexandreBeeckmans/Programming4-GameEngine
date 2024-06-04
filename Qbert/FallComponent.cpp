#include "FallComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

#include "GridMoveComponent.h"


qbert::FallComponent::FallComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::FallComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::FallComponent::SetFallDirection()
{
	m_FallTarget = m_pMoveComponent->GetCurrentTile()->GetStartPoint() - glm::vec2(0, GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h / 2);


	glm::vec2 objectToDestination{ m_FallTarget - glm::vec2{ GetWorldPosition().x, GetWorldPosition().y } };
	m_FallDirection = glm::normalize(objectToDestination);

	m_MaxDistanceToFall = glm::length(objectToDestination);
	m_AccumulatedDistanceToFall = 0.0f;
}

void qbert::FallComponent::UpdateFall()
{
	const glm::vec2 displacement{ m_FallDirection * m_FallSpeed * dae::EngineTime::GetInstance().GetDeltaTime() };
	GetOwner()->Translate(displacement);

	m_AccumulatedDistanceToFall += glm::length(displacement * dae::ImageComponent::GetSpriteScale());
}

bool qbert::FallComponent::HasReachedFallPos() const
{
	return m_AccumulatedDistanceToFall >= m_MaxDistanceToFall;
}
