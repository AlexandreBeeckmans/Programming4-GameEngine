#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <iostream>


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

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
