#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>


//#include "Font.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() = default;

		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);

		TextComponent(const TextComponent& other) = default;
		TextComponent(TextComponent&& other) = default;
		TextComponent& operator=(const TextComponent& other) = default;
		TextComponent& operator=(TextComponent&& other) = default;

	private:

		void InitTexture();

		std::string m_Text{};
		std::shared_ptr<Font> m_pFont{};
		std::shared_ptr<Texture2D>m_pTextTexture{};
	};
}


