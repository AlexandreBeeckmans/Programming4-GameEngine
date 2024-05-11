#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::ImageComponent::ImageComponent(GameObject* pGameObject, const std::string& filePath, const bool isVisible, const float relativeX, const float relativeY, const int nbRows, const int nbCols, const int rowNb, const int colNb) :
	BaseComponent(pGameObject),
	m_MaxCol(nbCols),
	m_MaxRow(nbRows),
	m_Col(colNb),
	m_Row(rowNb),
	m_IsVisible(isVisible)
{
	m_RelativePosition.SetPosition(relativeX, relativeY, 0);

	if (filePath.length() > 0)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
	}

	m_ImageShape.x = static_cast<int>(GetOwner()->GetWorldPosition().x + m_RelativePosition.GetPosition().x);
	m_ImageShape.y = static_cast<int>(GetOwner()->GetWorldPosition().y + m_RelativePosition.GetPosition().y);
	m_ImageShape.w = m_pTexture->GetSize().x / nbCols;
	m_ImageShape.h = m_pTexture->GetSize().y / nbRows;

	
	m_SrcRect.w = m_pTexture->GetSize().x / nbCols;
	m_SrcRect.h = m_pTexture->GetSize().y / nbRows;
	m_SrcRect.x = colNb * m_SrcRect.w;
	m_SrcRect.y = rowNb * m_SrcRect.h;
	
}

void dae::ImageComponent::Update()
{
	BaseComponent::Update();
	UpdateShape();
}

void dae::ImageComponent::Render() const
{
	if (!m_pTexture) return;
	if (!m_IsVisible) return;
	
	/*const auto& pos = GetOwner()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_RelativePosition.GetPosition().x, pos.y + m_RelativePosition.GetPosition().y);*/
	Renderer::GetInstance().RenderTexture(m_pTexture.get(), m_ImageShape, m_SrcRect);
}

void dae::ImageComponent::SetTexture(SDL_Texture* pTexture)
{
	m_pTexture = nullptr;
	m_pTexture = std::make_unique<Texture2D>(pTexture);
}

void dae::ImageComponent::UpdateSource()
{
	m_SrcRect.x = m_Col * m_SrcRect.w;
	m_SrcRect.y = m_Row * m_SrcRect.h;
}

void dae::ImageComponent::UpdateShape()
{
	m_ImageShape.x = static_cast<int>(GetOwner()->GetWorldPosition().x + m_RelativePosition.GetPosition().x);
	m_ImageShape.y = static_cast<int>(GetOwner()->GetWorldPosition().y + m_RelativePosition.GetPosition().y);
}

void dae::ImageComponent::SetVisible(const bool isVisible)
{
	m_IsVisible = isVisible;
}

void dae::ImageComponent::UpdateRow()
{
	++m_Row %= m_MaxRow;
	UpdateSource();
}

void dae::ImageComponent::SetColumn(int col)
{
	m_Col = col;
	UpdateSource();
}
