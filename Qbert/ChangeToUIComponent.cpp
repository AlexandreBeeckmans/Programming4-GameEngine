#include "ChangeToUIComponent.h"

#include "EngineTime.h"
#include "ImageComponent.h"

qbert::ChangeToUIComponent::ChangeToUIComponent(dae::GameObject* pOwner, const std::vector<dae::ImageComponent*>& arrows):
BaseComponent(pOwner), m_Arrows{arrows},
m_Steps{ static_cast<int>((arrows.size() + 1) / 2) + 1 }
{
}

void qbert::ChangeToUIComponent::Update()
{
	m_AccumulatedTime += dae::EngineTime::GetInstance().GetDeltaTime();

	if(m_AccumulatedTime >= m_BlinkTime)
	{
		m_AccumulatedTime = 0;
		++m_CurrentStep %= m_Steps;

		for(int i{0}; i < m_Steps - 1; ++i)
		{
			bool isVisible{ i < m_CurrentStep };

			m_Arrows[i]->SetVisible(isVisible);

			m_Arrows[m_Arrows.size() - 1 - i]->SetVisible(isVisible);
		}
	}
}
