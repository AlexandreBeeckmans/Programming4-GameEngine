#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

#include "iostream"

dae::ImageComponent::ImageComponent(GameObject* pGameObject, const std::string& filePath, const float relativeX, const float relativeY) :
	BaseComponent::BaseComponent(pGameObject)
{
	m_RelativePosition.SetPosition(relativeX, relativeY, 0);
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}

void dae::ImageComponent::Render() const
{
	const auto& pos = m_pParent->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture.get(), pos.x + m_RelativePosition.GetPosition().x, pos.y + m_RelativePosition.GetPosition().y);
}
