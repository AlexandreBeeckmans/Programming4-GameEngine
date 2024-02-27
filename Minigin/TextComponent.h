#pragma once
#include "ImageComponent.h"
#include <string>
#include <memory>

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;

	class TextComponent : public ImageComponent
	{
	public:
		TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> pFont);

		void SetText(const std::string& text);

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:

		void InitTexture();

		std::string m_Text{};
		std::shared_ptr<Font> m_pFont{};
	};
}


