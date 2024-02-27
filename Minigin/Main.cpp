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
#include "RotatingComponent.h"

#include "Font.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgrounObject = std::make_shared<dae::GameObject>();

	backgrounObject->AddComponent<dae::ImageComponent>("background.tga", 0.0f, 0.0f);
	backgrounObject->AddComponent<dae::ImageComponent>("logo.tga", 220.0f, 200.0f);
	backgrounObject->SetPosition(0, 0);
	scene.Add(backgrounObject);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto titleObject{ std::make_shared<dae::GameObject>() };

	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	titleObject->SetPosition(80, 20);
	scene.Add(titleObject);

	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::RenderFPSComponent>(fontFps);
	fpsObject->SetPosition(50, 150);
	scene.Add(fpsObject);


	auto parentObject = std::make_shared<dae::GameObject>();
	parentObject->AddComponent<dae::ImageComponent>("sprite1.png");
	parentObject->SetPosition(200, 300);
	parentObject->AddComponent<dae::RotatingComponent>();
	scene.Add(parentObject);

	auto childObject = std::make_shared<dae::GameObject>();
	childObject->AddComponent<dae::ImageComponent>("sprite2.png");
	childObject->SetPosition(15, 15);
	childObject->AddComponent<dae::RotatingComponent>();
	scene.Add(childObject);

	childObject->SetParent(parentObject.get(), false);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}