#include "QbertMoveComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"

qbert::QbertMoveComponent::QbertMoveComponent(dae::GameObject* owner):
BaseComponent(owner)
{
}

void qbert::QbertMoveComponent::SetDirection(const glm::vec2& direction)
{
	if(direction.x > 0)
	{
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
	}
}
