#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(dae::GameObject* pGameObject) :
	m_pOwnerObject{pGameObject}
{
}

const dae::GameObject* dae::BaseComponent::GetOwner() const
{
	return m_pOwnerObject;
}