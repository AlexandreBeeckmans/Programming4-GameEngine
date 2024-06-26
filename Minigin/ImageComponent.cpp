#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"
float dae::ImageComponent::m_SpriteScale = 2.0f;


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
	m_ImageShape.w = static_cast<int>(static_cast<float>(m_pTexture->GetSize().x / nbCols) * m_SpriteScale);
	m_ImageShape.h = static_cast<int>(static_cast<float>(m_pTexture->GetSize().y / nbRows) * m_SpriteScale);

	
	m_SrcRect.w = m_pTexture->GetSize().x / nbCols;
	m_SrcRect.h = m_pTexture->GetSize().y / nbRows;
	m_SrcRect.x = colNb * m_SrcRect.w;
	m_SrcRect.y = rowNb * m_SrcRect.h;

	m_StartingDestHeight = static_cast<float>(m_ImageShape.h);
	m_StartingSrcHeight = static_cast<float>(m_SrcRect.h);
	m_StartingDestWidth = static_cast<float>(m_ImageShape.w);
	m_StartingSrcWidth = static_cast<float>(m_SrcRect.w);
	
}

void dae::ImageComponent::Update()
{
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
	m_SrcRect.w = m_pTexture->GetSize().x / m_MaxCol;
	m_SrcRect.h = m_pTexture->GetSize().y / m_MaxRow;
	m_SrcRect.x = m_Col * m_SrcRect.w;
	m_SrcRect.y = m_Row * m_SrcRect.h;
}

void dae::ImageComponent::UpdateShape()
{
	m_ImageShape.x = static_cast<int>(GetOwner()->GetWorldPosition().x + m_RelativePosition.GetPosition().x);
	m_ImageShape.y = static_cast<int>(GetOwner()->GetWorldPosition().y + m_RelativePosition.GetPosition().y);

	
}

void dae::ImageComponent::MakeShapeFitTexture()
{
	m_ImageShape.w = m_pTexture->GetSize().x / m_MaxCol;
	m_ImageShape.h = m_pTexture->GetSize().y / m_MaxRow;
}

void dae::ImageComponent::SetWidth(const int newWidth, bool conserveProportions)
{
	if(conserveProportions)
	{
		const float percentage = static_cast<float>(newWidth) / static_cast<float>(m_ImageShape.w);
		m_ImageShape.h = static_cast<int>(static_cast<float>(m_ImageShape.h) * percentage);
	}
	m_ImageShape.w = newWidth;
}

void dae::ImageComponent::SetHeight(const int newHeight)
{
	m_ImageShape.h = newHeight;
}

void dae::ImageComponent::ReduceHeight(const float percentage)
{
	m_SrcRect.h = static_cast<int>(percentage * m_StartingSrcHeight);
	m_ImageShape.h = static_cast<int>(percentage * m_StartingDestHeight);
}

void dae::ImageComponent::ReduceWidth(const float percentage)
{
	m_SrcRect.w = static_cast<int>(percentage * m_StartingSrcWidth);
	m_ImageShape.w = static_cast<int>(percentage * m_StartingDestWidth);
}

void dae::ImageComponent::Rescale(const float percentage)
{
	m_ImageShape.h = static_cast<int>(percentage * m_StartingDestHeight);
	m_ImageShape.w = static_cast<int>(percentage * m_StartingDestWidth);
}

void dae::ImageComponent::SetVisible(const bool isVisible)
{
	m_IsVisible = isVisible;
}

void dae::ImageComponent::SetRelativePosition(const float x, const float y)
{
	m_RelativePosition.SetPosition(x, y, 0);
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

void dae::ImageComponent::SetRow(const int row)
{
	m_Row = row;
	UpdateSource();
}
