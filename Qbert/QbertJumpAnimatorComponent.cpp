#include "QbertJumpAnimatorComponent.h"

#include "GridMoveComponent.h"

qbert::QbertJumpAnimatorComponent::QbertJumpAnimatorComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::QbertJumpAnimatorComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::QbertJumpAnimatorComponent::SetJumpSprite() const
{
	switch (m_pMoveComponent->GetGridDirection())
	{
	case(GridDirection::BOTTOMRIGHT):
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
		break;

	case(GridDirection::BOTTOMLEFT):
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		break;

	case(GridDirection::TOPRIGHT):
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(0);
		break;

	case(GridDirection::TOPLEFT):
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(1);
		break;
	}
}
