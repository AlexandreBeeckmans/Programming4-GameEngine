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
		ImageComponent(GameObject* pGameObject, const std::string& filePath = "", const bool isVisible = true, const float relativeX = 0, const float relativeY = 0, const int nbRows = 1, const int nbCols = 1, const int rowNb = 0, const int colNb = 0);
		virtual ~ImageComponent() override = default;


		ImageComponent(const ImageComponent& other) = delete;
		ImageComponent(ImageComponent&& other) = delete;
		ImageComponent& operator=(const ImageComponent& other) = delete;
		ImageComponent& operator=(ImageComponent&& other) = delete;

		virtual void Update() override;

		void virtual Render() const override;

		SDL_Rect GetShape() const { return m_ImageShape; }
		void SetRelativePosition(const float x, const float y);

		
		void UpdateRow();

		void SetColumn(int col);
		void SetRow(const int row);

		int GetColumn() const { return m_Col; }

		void UpdateShape();
		void MakeShapeFitTexture();
		void SetWidth(const int newWidth);
		void SetHeight(const int newHeight);

		void ReduceHeight(const float percentage);
		void ReduceWidth(const float percentage);
		void Rescale(const float percantage);


		void SetVisible(const bool isVisible);

		static void SetSpriteScale(const float scale) { m_SpriteScale = scale; }
		static float GetSpriteScale() { return m_SpriteScale; }




	protected:
		void SetTexture(SDL_Texture* pTexture);
		void UpdateSource();
		
		

	private:
		static float m_SpriteScale;


		std::unique_ptr<Texture2D> m_pTexture{};
		Transform m_RelativePosition{};

		SDL_Rect m_ImageShape{};
		SDL_Rect m_SrcRect{};

		const int m_MaxCol{ 1 };
		const int m_MaxRow{ 1 };
		int m_Col{ 0 };
		int m_Row{ 0 };

		bool m_IsVisible{ true };

		float m_StartingDestHeight{};
		float m_StartingSrcHeight{};
		float m_StartingDestWidth{};
		float m_StartingSrcWidth{};
	};
}


