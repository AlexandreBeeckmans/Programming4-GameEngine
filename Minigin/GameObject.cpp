#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <iostream>


dae::GameObject::GameObject(std::unique_ptr<BaseObserver> pObserver)
{
	m_pEventSubject = std::make_unique<Subject>();
	m_pEventSubject->AddObserver(std::move(pObserver));
}

void dae::GameObject::Update()
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& pComp : m_pComponents)
	{
		pComp->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto& pComp : m_pComponents)
	{
		pComp->LateUpdate();
	}
}


void dae::GameObject::Render() const
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void dae::GameObject::RenderGui() const
{
	for (auto& pComp : m_pComponents)
	{
		pComp->RenderGui();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
	SetPositionDirty();
}

void dae::GameObject::RemoveAllDeadComponent()
{

	for (auto& component : m_pComponents)
	{
		if (component->GetIsDead())
		{
			component = nullptr;
		}
	}

	std::erase_if(m_pComponents, [](std::unique_ptr<dae::BaseComponent>& component)
		{
			return !component;
		});
}

dae::GameObject* dae::GameObject::GetParent() const
{
	if (!m_pParent) return nullptr;
	return m_pParent;
}

bool dae::GameObject::IsChild(GameObject* pParent) const
{
	if (pParent == nullptr) return false;
	return pParent->GetParent() == this;
}

void dae::GameObject::SetParent(GameObject* pParent, const bool keepWorldPosition)
{
	//Check if valid
	if (pParent == this || pParent == m_pParent || IsChild(pParent) ) return;

	if (pParent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetLocalPosition() - pParent->GetWorldPosition());
		SetPositionDirty();
	}


	//Remove itself from the previous parent
	if(m_pParent)
		m_pParent->RemoveChild(this);

	//Set the given parent on itself
	m_pParent = pParent;

	//Add himself to the new parent
	if(pParent)
		pParent->AddChild(this);
}
void dae::GameObject::DetachFromParent()
{
	SetParent(nullptr);
}



void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	std::erase(m_pChildren, pChild);
}




glm::vec3 dae::GameObject::GetLocalPosition() const
{
	return m_transform.GetPosition();
}
glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_IsPositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_transform.SetPosition(pos.x, pos.y, pos.z);
	SetPositionDirty();
}


void dae::GameObject::UpdateWorldPosition()
{
	if (m_IsPositionDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPosition = GetLocalPosition();
		else
			m_WorldPosition = m_pParent->GetWorldPosition() + GetLocalPosition();
	}
	m_IsPositionDirty =  false;
}

void dae::GameObject::SetPositionDirty()
{
	m_IsPositionDirty = true;

	for (auto child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}


void dae::GameObject::Notify(const Event& event)
{
	m_pEventSubject->NotifyObservers(event, this);
}