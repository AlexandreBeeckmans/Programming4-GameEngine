#include "GuiEx1Component.h"

#include "GameObject.h"
#include <imgui.h>

dae::GuiEx1Component::GuiEx1Component(dae::GameObject* pParent) :
	BaseGuiComponent::BaseGuiComponent(pParent, "Exercise 1"),
	m_IntGraph{std::make_unique<Graph<int>>()}
{
}

void dae::GuiEx1Component::RenderGui() const
{
	ImGui::Begin(GetName());

	//Integers

	ImGui::InputInt("sample", &m_IntGraph->samples);

	if (ImGui::Button("Trash The Cache with Integer"))
	{
		m_IntGraph->canCompute = true;
		m_IntGraph->hasComputedOnce = true;
		ImGui::Text("Wait for It...");
	}
		
	ImColor color{ 255,0,0 };
	if(m_IntGraph->hasComputedOnce)
		m_IntGraph->Render(color);

	ImGui::End();
}
