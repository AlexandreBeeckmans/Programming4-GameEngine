#include "BlinkingComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

qbert::BlinkingComponent::BlinkingComponent(dae::GameObject* m_pOwner, const float blinkingTime, const bool isDefaultActivated) :
BaseComponent(m_pOwner),
m_IsActive{isDefaultActivated},
m_MaxBlinkingTime{blinkingTime}
{
}

void qbert::BlinkingComponent::Update()
{
	if (!m_IsActive) return;

	m_AccumulatedTime += dae::EngineTime::GetInstance().GetDeltaTime();
	if(m_AccumulatedTime >= m_MaxBlinkingTime)
	{
		GetOwner()->SetVisible(!GetOwner()->IsVisible());
		m_AccumulatedTime = 0.0f;
	}
}

void qbert::BlinkingComponent::SetActive(const bool isActive)
{
	m_IsActive = isActive;
	m_AccumulatedTime = 0.0f;

	GetOwner()->SetVisible(true);
}
