#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <iostream>


void dae::GameObject::Update(const float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
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
