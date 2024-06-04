#include "BubbleManagerComponent.h"
#include"ImageComponent.h"

qbert::BubbleManagerComponent::BubbleManagerComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
}

void qbert::BubbleManagerComponent::SetBubbleImage(dae::ImageComponent* pImageComponent)
{
	m_pBubbleImage = pImageComponent;
}

void qbert::BubbleManagerComponent::ShowBubble(const bool showBubble) const
{
	if (!m_pBubbleImage) return;


	m_pBubbleImage->SetVisible(showBubble);

}
