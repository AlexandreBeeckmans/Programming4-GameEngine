#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

#include <SDL_ttf.h>

dae::ImageComponent::ImageComponent(GameObject* pGameObject, const std::string& filePath, const float relativeX, const float relativeY) :
	BaseComponent::BaseComponent(pGameObject)
{
	m_RelativePosition.SetPosition(relativeX, relativeY, 0);

	if (filePath.length() > 0)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
	}
	
}

void dae::ImageComponent::Render() const
{
	if (!m_pTexture) return; 
	const auto& pos = GetOwner()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture.get(), pos.x + m_RelativePosition.GetPosition().x, pos.y + m_RelativePosition.GetPosition().y);
}

void dae::ImageComponent::SetTexture(SDL_Texture* pTexture)
{
	m_pTexture = nullptr;
	m_pTexture = std::make_unique<Texture2D>(pTexture);
}
