#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ImageComponent;
}

namespace qbert
{
	class GridMoveComponent;
}

namespace qbert
{
	class SlickAnimatorComponent final : public dae::BaseComponent
	{
	public:
		SlickAnimatorComponent(dae::GameObject* owner);
		virtual ~SlickAnimatorComponent() override = default;


		SlickAnimatorComponent(const SlickAnimatorComponent& other) = delete;
		SlickAnimatorComponent(SlickAnimatorComponent&& other) = delete;
		SlickAnimatorComponent& operator=(const SlickAnimatorComponent& other) = delete;
		SlickAnimatorComponent& operator=(SlickAnimatorComponent&& other) = delete;

		virtual void Init() override;
		void SetSprite();

	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };
		dae::ImageComponent* m_pImageComponent{ nullptr };
	};
}


