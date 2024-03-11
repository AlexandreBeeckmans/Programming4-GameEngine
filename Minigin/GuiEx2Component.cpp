#include "GuiEx2Component.h"

#include "GameObject.h"
#include <imgui.h>

dae::GuiEx2Component::GuiEx2Component(dae::GameObject* pParent) :
	BaseGuiComponent::BaseGuiComponent(pParent, "Exercise 2"),
	m_GOGraph{ std::make_unique<Graph<TrashGameObject>>() },
	m_GOAltGraph{ std::make_unique<Graph<TrashGameObjectAlt>>() }
{
}

void dae::GuiEx2Component::RenderGui() const
{
	ImU32 colors[2]
	{
		ImColor{0,255,0},
		ImColor{0,0,255}
	};

	ImGui::Begin(GetName());

	//GO
	ImGui::InputInt("sample", &m_GOGraph->samples);
	m_GOAltGraph->samples = m_GOGraph->samples;

	if (ImGui::Button("Trash The Cache with 3D GameObject"))
	{
		m_GOGraph->canCompute = true;
		m_GOGraph->hasComputedOnce = true;
		ImGui::Text("Wait for It...");
	}

	if (m_GOGraph->hasComputedOnce)
		m_GOGraph->Render(colors[0]);

	//GO Alt
	if (ImGui::Button("Trash The Cache with GameObject 3D alt"))
	{
		m_GOAltGraph->canCompute = true;
		m_GOAltGraph->hasComputedOnce = true;
	}
	
	if (m_GOAltGraph->hasComputedOnce)
	{
		m_GOAltGraph->Render(colors[1]);
	}


	//Combined
	//Combined graph
	if (m_GOAltGraph->hasComputedOnce && m_GOGraph->hasComputedOnce)
	{
		DisplayCombinedGraph(colors);
	}




	ImGui::End();
}

void dae::GuiEx2Component::DisplayCombinedGraph(ImU32* colors) const
{
	ImGui::PlotConfig testConfig{};

	float xValues[11]{ 1,2,3,4,5,6,7,8,9,10,11 };

	testConfig.values.xs = xValues;
	testConfig.values.count = 11;

	float* yValues1{ m_GOAltGraph->times };
	float* yValues2{ m_GOGraph->times };

	const float** yValues{ new const float* [2] {yValues1, yValues2} };
	testConfig.values.ys_list = yValues;
	testConfig.values.ys_count = 2;

	testConfig.values.colors = colors;


	testConfig.scale = { -1, m_GOAltGraph->times[0] };

	testConfig.tooltip.show = true;
	testConfig.tooltip.format = "x=%.2f, y=%.2f";
	testConfig.grid_x.show = true;
	testConfig.grid_y.show = true;
	testConfig.frame_size = ImVec2(200, 100);
	testConfig.line_thickness = 2.f;

	ImGui::Plot("combined", testConfig);

	delete[] yValues;
}