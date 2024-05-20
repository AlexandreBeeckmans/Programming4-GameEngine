#include "TextComponent.h"

#include<iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "GameObject.h"


dae::TextComponent::TextComponent(GameObject* pGameObject, const std::string& text,const Font& font):
	ImageComponent(pGameObject),
	m_Text(text),
	m_pFont{std::make_unique<Font>(font)}
{
	InitTexture();
	MakeShapeFitTexture();
	UpdateSource();
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	InitTexture();
	MakeShapeFitTexture();
	UpdateSource();
}

void dae::TextComponent::InitTexture()
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	SetTexture(texture);
}