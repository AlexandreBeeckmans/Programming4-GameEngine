#include "RenderFPSComponent.h"
#include "FPS.h"
#include "TextComponent.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Font.h"

#include "Time.h"

#include<sstream>
#include <iomanip>


dae::RenderFPSComponent::RenderFPSComponent(GameObject* pGameObject, std::shared_ptr<Font> pFont) :
	TextComponent::TextComponent(pGameObject, "Hello", pFont)
{
	if (!GetOwner()->HasComponent<FPSComponent>())
	{
		GetOwner()->AddComponent<FPSComponent>(pGameObject);
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
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << m_AccumulatedFPS / m_IterationCount << "FPS";

		std::string fpsString{ stream.str() };
		SetText(fpsString);

		m_AccumulatedTime = 0.0f;
		m_AccumulatedFPS = 0.0f;
		m_IterationCount = 0;
	}
}
