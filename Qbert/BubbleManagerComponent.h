#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ImageComponent;
}

namespace qbert
{
	class BubbleManagerComponent final : public dae::BaseComponent
	{
	public:
		BubbleManagerComponent(dae::GameObject* owner);
		virtual ~BubbleManagerComponent() override = default;


		BubbleManagerComponent(const BubbleManagerComponent& other) = delete;
		BubbleManagerComponent(BubbleManagerComponent&& other) = delete;
		BubbleManagerComponent& operator=(const BubbleManagerComponent& other) = delete;
		BubbleManagerComponent& operator=(BubbleManagerComponent&& other) = delete;

		void SetBubbleImage(dae::ImageComponent* pImageComponent);
		void ShowBubble(bool showBubble) const;

	private:
		dae::ImageComponent* m_pBubbleImage{ nullptr };
	};
}


