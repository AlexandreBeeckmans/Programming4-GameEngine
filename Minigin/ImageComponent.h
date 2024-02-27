#pragma once
#include "BaseComponent.h"
#include "Transform.h"

#include <memory>
#include <string>

struct SDL_Texture;

namespace dae
{
	class Texture2D;
	

	class ImageComponent : public BaseComponent
	{
	public:
		ImageComponent(GameObject*, const std::string& filePath = "", const float relativeX = 0, const float relativeY = 0);
		~ImageComponent() { m_pTexture = nullptr; };


		ImageComponent(const ImageComponent& other) = default;
		ImageComponent(ImageComponent&& other) = default;
		ImageComponent& operator=(const ImageComponent& other) = default;
		ImageComponent& operator=(ImageComponent&& other) = default;

		void virtual Render() const override;

	protected:
		void SetTexture(SDL_Texture* pTexture);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Transform m_RelativePosition{};
	};
}


