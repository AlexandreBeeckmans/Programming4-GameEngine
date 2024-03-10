#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

//#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#include <imgui_plot.h>

//#include <memory>

#include "TrashTheCache.h"



//template <class T>
//void dae::Graph::Render()
//{
//	//if (canCompute)
//	//{
//		//canCompute = false;
//		const size_t samples{ 100000 };
//		T* integerOperations{ new T[samples]{} };
//		dae::TrashCache<T>(integerOperations, samples, times);
//		delete[] integerOperations;
//	//}
//
//
//	ImGui::PlotConfig testConfig{};
//
//	float xValues[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
//	float* yValues{ times };
//
//	testConfig.values = { xValues, yValues, 11 };
//	testConfig.scale = { -1, times[0] };
//
//	testConfig.tooltip.show = true;
//	testConfig.tooltip.format = "x=%.2f, y=%.2f";
//	testConfig.grid_x.show = true;
//	testConfig.grid_y.show = true;
//	testConfig.frame_size = ImVec2(200, 100);
//	testConfig.line_thickness = 2.f;
//
//	ImGui::Plot("test", testConfig);
//}

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();


	//m_ComputeInt = true;
	//m_ComputeGO = true;
	//m_ComputeGOAlt = true;

	m_IntGraph = std::make_unique<Graph<int>>();
	m_GOGraph = std::make_unique<Graph<TrashGameObject>>();
	m_GOAltGraph = std::make_unique<Graph<TrashGameObjectAlt>>();
	
}

void dae::Renderer::Render() const
{

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//SceneManager::GetInstance().RenderGUI();
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("sample", &m_IntGraph->samples);

	
	//Integers
	if (ImGui::Button("Trash The Cache with Integer"))
	{
		m_IntGraph->canCompute = true;
		m_IntGraph->hasComputedOnce = true;
	}
		
	if(m_IntGraph->hasComputedOnce)
		m_IntGraph->Render();
	


	if (ImGui::Button("Trash The Cache with GameObject 3D"))
	{
		m_GOGraph->canCompute = true;
		m_GOGraph->hasComputedOnce = true;
	}
	
	if(m_GOGraph->hasComputedOnce)
		m_GOGraph->Render();


	if (ImGui::Button("Trash The Cache with GameObject 3D alt"))
	{
		m_GOAltGraph->canCompute = true;
		m_GOAltGraph->hasComputedOnce = true;
	}
	
	if (m_GOAltGraph->hasComputedOnce)
	{
		m_GOAltGraph->Render();
	}
	
	//Combined graph
	if (m_GOAltGraph->hasComputedOnce && m_GOGraph->hasComputedOnce)
	{
		ImGui::PlotConfig testConfig{};

		float xValues[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
		//float* yValues{ m_GOGraph->times };

		testConfig.values.xs = xValues;
		testConfig.values.count = 11;

		float* yValues1{ m_GOAltGraph->times };
		float* yValues2{ m_GOGraph->times };

		const float** yValues{ new const float* [2] {yValues1, yValues2} };
		testConfig.values.ys_list = yValues;
		testConfig.values.ys_count = 2;

		ImU32 colors[2]{ 0,0 };
		testConfig.values.colors = { colors };


		testConfig.scale = { -1, m_GOAltGraph->times[0] };

		testConfig.tooltip.show = true;
		testConfig.tooltip.format = "x=%.2f, y=%.2f";
		testConfig.grid_x.show = true;
		testConfig.grid_y.show = true;
		testConfig.frame_size = ImVec2(200, 100);
		testConfig.line_thickness = 2.f;

		ImGui::Plot("combined", testConfig);
	}

	ImGui::End();

	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }



