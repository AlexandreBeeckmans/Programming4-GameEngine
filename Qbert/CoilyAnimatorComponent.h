#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;
}

namespace dae
{
	class ImageComponent;
}

namespace qbert
{
	class CoilyAnimatorComponent final : public dae::BaseComponent
	{
	public:
		CoilyAnimatorComponent(dae::GameObject* owner);
		virtual ~CoilyAnimatorComponent() override = default;


		CoilyAnimatorComponent(const CoilyAnimatorComponent& other) = delete;
		CoilyAnimatorComponent(CoilyAnimatorComponent&& other) = delete;
		CoilyAnimatorComponent& operator=(const CoilyAnimatorComponent& other) = delete;
		CoilyAnimatorComponent& operator=(CoilyAnimatorComponent&& other) = delete;

		virtual void Init() override;

		void SetWaitingSprite() const;
		void SetArrivingSprite(const int column) const;
		void SetJumpingSprite() const;

		void SetVisible() const;

	private:
		dae::ImageComponent* m_pImageComponent{nullptr};
		GridMoveComponent* m_pMoveComponent{ nullptr };
	};
}


