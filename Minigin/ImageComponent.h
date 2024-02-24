#pragma once
#include "BaseComponent.h"
#include "Transform.h"

#include <memory>
#include <string>

namespace dae
{
	class Texture2D;

	class ImageComponent final : public BaseComponent
	{
	public:
		ImageComponent(GameObject* pGameObject, const std::string& filePath, const float relativeX, const float relativeY);
		~ImageComponent() { m_pTexture = nullptr; };

		ImageComponent(const ImageComponent& other) = default;
		ImageComponent(ImageComponent&& other) = default;
		ImageComponent& operator=(const ImageComponent& other) = default;
		ImageComponent& operator=(ImageComponent&& other) = default;

		void virtual Render() const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Transform m_RelativePosition{};
	};
}


