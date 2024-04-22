#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class UIComponent : public BaseComponent, public Observer
	{
	public:
		UIComponent(GameObject* m_pParent, TextComponent* pScoreTextComponent, TextComponent* pLifeTextComponent);
		void UpdateObserver() override;
	private:
		TextComponent* m_ScoreTextComponent{};
		TextComponent* m_LifeTextComponent{};
	};
}


