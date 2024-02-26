#include "RenderFPSComponent.h"
#include "FPS.h"
#include "TextComponent.h"
#include "ResourceManager.h"

#include "Time.h"

#include<sstream>
#include <iomanip>


dae::RenderFPSComponent::RenderFPSComponent(GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_pFPSComponent{ std::make_shared<dae::FPSComponent>(pGameObject) }
{
	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pTextComponent = std::make_shared<dae::TextComponent>(pGameObject, "0", font);
}

void dae::RenderFPSComponent::Update()
{
	m_AccumulatedTime += Time::GetInstance().GetDeltaTime();

	if (m_AccumulatedTime >= m_TimeToRender)
	{
		m_AccumulatedTime = 0.0f;

		m_pFPSComponent->Update();

		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << m_pFPSComponent->GetFPS();

		std::string fpsString{ stream.str() + "FPS" };
		m_pTextComponent->SetText(fpsString);
	}
}

void dae::RenderFPSComponent::Render() const
{
	m_pTextComponent->Render();
}
