#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <iostream>


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}


void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
