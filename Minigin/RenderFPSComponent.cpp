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

	if (m_AccumulatedTime >= m_TimeToRender)
	{
		m_AccumulatedTime = 0.0f;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << m_pFPSComponent->GetFPS() << "FPS";

		std::string fpsString{ stream.str() };
		SetText(fpsString);
	}
}
