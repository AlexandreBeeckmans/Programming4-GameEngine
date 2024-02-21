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
#include "TextObject.h"
#include "Scene.h"

#include "GameObject.h"
#include "FPS.h"
#include "TextComponent.h"
#include "Font.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to{ std::make_shared<dae::GameObject>() };
	to->AddComponent<dae::TextComponent>(dae::TextComponent{ to.get(), "Programming 4 Assignment", font});
	to->SetPosition(80, 20);
	scene.Add(to);

	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::FPSComponent>(fpsObject.get());
	fpsObject->AddComponent<dae::TextComponent>(dae::TextComponent{ fpsObject.get(), "0 FPS", font });
	fpsObject->SetPosition(50, 150);
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}