#include "BaseGuiComponent.h"
#include <imgui.h>

#include "GameObject.h"

dae::BaseGuiComponent::BaseGuiComponent(dae::GameObject* pParent, const std::string& name) :
	BaseComponent::BaseComponent{pParent},
	m_Name{name}
{}

void dae::BaseGuiComponent::RenderGui() const
{
	ImGui::Begin(m_Name.c_str());
	ImGui::End();
}
