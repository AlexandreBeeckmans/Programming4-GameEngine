#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Texture2D.h"

#include <memory>
#include <string>
#include <SDL.h>

struct SDL_Texture;

namespace dae
{
	class ImageComponent : public BaseComponent
	{
	public:
		ImageComponent(GameObject* owner, const std::string& filePath = "", const bool isVisible = true, const float relativeX = 0, const float relativeY = 0, const int nbRows = 1, const int nbCols = 1, const int rowNb = 0, const int colNb = 0);
		~ImageComponent() override { m_pTexture = nullptr; }


		ImageComponent(const ImageComponent& other) = delete;
		ImageComponent(ImageComponent&& other) = delete;
		ImageComponent& operator=(const ImageComponent& other) = delete;
		ImageComponent& operator=(ImageComponent&& other) = delete;

		virtual void Update() override;

		void virtual Render() const override;
		SDL_Rect GetShape() const { return m_ImageShape; }
		

		
		void UpdateRow();
		void SetColumn(int col);
		

		void UpdateShape();

		void SetVisible(const bool isVisible);
	protected:
		void SetTexture(SDL_Texture* pTexture);
		void UpdateSource();
		
		

	private:
		std::unique_ptr<Texture2D> m_pTexture{};
		Transform m_RelativePosition{};

		SDL_Rect m_ImageShape{};
		SDL_Rect m_SrcRect{};

		const int m_MaxCol{ 1 };
		const int m_MaxRow{ 1 };
		int m_Col{ 0 };
		int m_Row{ 0 };

		bool m_IsVisible{ true };
	};
}


