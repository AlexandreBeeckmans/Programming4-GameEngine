#include "RenderFPSComponent.h"
#include "FPS.h"
#include "TextComponent.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Font.h"

#include "Time.h"

#include<sstream>
#include <format>


dae::RenderFPSComponent::RenderFPSComponent(GameObject* pGameObject, std::shared_ptr<Font> pFont) :
	TextComponent::TextComponent(pGameObject, "Hello", pFont)
{
	if (!GetOwner()->HasComponent<FPSComponent>())
	{
		GetOwner()->AddComponent<FPSComponent>();
	}

	m_pFPSComponent = GetOwner()->GetComponent<FPSComponent>();
}

void dae::RenderFPSComponent::Update()
{
	if (!m_pFPSComponent) return;

	m_AccumulatedTime += Time::GetInstance().GetDeltaTime();
	m_AccumulatedFPS += m_pFPSComponent->GetFPS();
	++m_IterationCount;

	if (m_AccumulatedTime >= m_TimeToRender)
	{
		std::string fpsString{ std::format("{:.1f}", (m_AccumulatedFPS / m_IterationCount)) + "FPS" };
		SetText(fpsString);

		m_AccumulatedTime = 0.0f;
		m_AccumulatedFPS = 0.0f;
		m_IterationCount = 0;
	}
}
