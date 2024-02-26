#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "FPS.h"
#include "TextComponent.h"
#include "RenderFPSComponent.h"
#include "ImageComponent.h"

#include "Font.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgrounObject = std::make_shared<dae::GameObject>();

	backgrounObject->AddComponent<dae::ImageComponent>(backgrounObject.get(), "background.tga", 0.0f, 0.0f);
	backgrounObject->AddComponent<dae::ImageComponent>(backgrounObject.get(), "logo.tga", 220.0f, 200.0f);
	backgrounObject->SetPosition(0, 0);
	scene.Add(backgrounObject);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto titleObject{ std::make_shared<dae::GameObject>() };

	titleObject->AddComponent<dae::TextComponent>(titleObject.get(), "Programming 4 Assignment", font);
	titleObject->SetPosition(80, 20);
	scene.Add(titleObject);

	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::RenderFPSComponent>(fpsObject.get());
	fpsObject->SetPosition(50, 150);
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}