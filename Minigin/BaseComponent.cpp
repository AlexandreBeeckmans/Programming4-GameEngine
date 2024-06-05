#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(dae::GameObject* pGameObject) :
	m_pOwnerObject{pGameObject}
{
	
}

glm::vec3 dae::BaseComponent::GetWorldPosition() const
{
	return GetOwner()->GetWorldPosition();
}

const dae::GameObject* dae::BaseComponent::GetParent() const
{
	return GetOwner()->GetParent();
}

void dae::BaseComponent::SetParent(GameObject* newParent) const
{
	GetOwner()->SetParent(newParent, true);
}

void dae::BaseComponent::DetachFromParent() const
{
	GetOwner()->DetachFromParent();
}

void dae::BaseComponent::DetachAllChildren() const
{
	GetOwner()->DetachAllChildren();
}

void dae::BaseComponent::SetOwnerActive(const bool isActive) const
{
	GetOwner()->SetActive(isActive);
}

bool dae::BaseComponent::IsOwnerActive() const
{
	return m_pOwnerObject->IsActive();
}

dae::GameObject* dae::BaseComponent::GetOwner() const
{
	return m_pOwnerObject;
}
