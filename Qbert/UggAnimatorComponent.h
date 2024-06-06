#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ImageComponent;
}

namespace qbert
{
	class UggDirectionComponent;
	class MapComponent;

	class UggAnimatorComponent final : public dae::BaseComponent
	{
	public:
		UggAnimatorComponent(dae::GameObject* owner, MapComponent* pMap);
		virtual ~UggAnimatorComponent() override = default;


		UggAnimatorComponent(const UggAnimatorComponent& other) = delete;
		UggAnimatorComponent(UggAnimatorComponent&& other) = delete;
		UggAnimatorComponent& operator=(const UggAnimatorComponent& other) = delete;
		UggAnimatorComponent& operator=(UggAnimatorComponent&& other) = delete;

		virtual void Init() override;

	private:
		dae::ImageComponent* m_pImageComponent{ nullptr };
		MapComponent* m_pMap{ nullptr };

		UggDirectionComponent* m_pDirectionComponent{ nullptr };
	};
}


