#pragma once
#include "ImageComponent.h"
#include <string>
#include <memory>
#include "Font.h"

namespace dae
{
	//class Font;
	class GameObject;

	class TextComponent : public ImageComponent
	{
	public:
		TextComponent(GameObject* pGameObject, const std::string& text, const Font& font);

		void SetText(const std::string& text);

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:

		void InitTexture();

		std::string m_Text{};
		std::unique_ptr<Font> m_pFont{};
	};
}


