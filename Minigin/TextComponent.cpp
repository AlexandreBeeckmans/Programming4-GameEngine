#include "TextComponent.h"

#include<iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"


dae::TextComponent::TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<dae::Font> font):
	BaseComponent::BaseComponent(pGameObject),
	m_Text(text),
	m_pFont(std::move(font)),
	m_pTextTexture{nullptr}
{
	InitTexture();
}

void dae::TextComponent::Update(const float deltaTime)
{
	std::cout << "Text Component Update : " << deltaTime << std::endl;
}
void dae::TextComponent::Render()
{
	if (m_pTextTexture != nullptr)
	{
		const auto& pos = m_pParent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	InitTexture();
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

	m_pTextTexture = std::make_shared<Texture2D>(texture);
	m_pParent->SetTexture(m_pTextTexture);
}