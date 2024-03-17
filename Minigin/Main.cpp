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
#include "InputManager.h"

#include "Scene.h"

#include "GameObject.h"
#include "FPS.h"
#include "TextComponent.h"
#include "RenderFPSComponent.h"
#include "ImageComponent.h"
#include "RotatingComponent.h"
#include "MoveComponent.h"

#include "GuiEx1Component.h"
#include "GuiEx2Component.h"

#include "Font.h"

#include "Controller.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgrounObject = std::make_shared<dae::GameObject>();

	backgrounObject->AddComponent<dae::ImageComponent>("background.tga", 0.0f, 0.0f);
	backgrounObject->AddComponent<dae::ImageComponent>("logo.tga", 220.0f, 200.0f);
	backgrounObject->SetLocalPosition(0, 0);
	scene.Add(backgrounObject);


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto titleObject{ std::make_shared<dae::GameObject>() };

	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", *font.get());
	titleObject->SetLocalPosition(80, 20);
	scene.Add(titleObject);

	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::RenderFPSComponent>(*fontFps.get());
	fpsObject->SetLocalPosition(50, 150);
	scene.Add(fpsObject);

	auto parentObject = std::make_shared<dae::GameObject>();
	parentObject->AddComponent<dae::ImageComponent>("sprite1.png");
	parentObject->SetLocalPosition(15, 15);
	parentObject->AddComponent<dae::MoveComponent>();

	dae::InputManager::GetInstance().SetMoveKeyboardCommandActor(parentObject.get());

	scene.Add(parentObject);

	auto childObject = std::make_shared<dae::GameObject>();
	childObject->AddComponent<dae::ImageComponent>("sprite2.png");
	childObject->SetLocalPosition(150, 15);
	childObject->AddComponent<dae::MoveComponent>(2 * parentObject->GetComponent<dae::MoveComponent>()->GetSpeed());

	dae::InputManager::GetInstance().AddController<dae::GamepadController>(childObject.get());

	scene.Add(childObject);

	auto centerOfRotationObject{ std::make_shared<dae::GameObject>() };
	centerOfRotationObject->SetLocalPosition(200, 300);
	scene.Add(centerOfRotationObject);
	

	/*auto guiObjectEx1 = std::make_shared<dae::GameObject>();
	guiObjectEx1->AddComponent<dae::GuiEx1Component>();
	scene.Add(guiObjectEx1);

	auto guiObjectEx2 = std::make_shared<dae::GameObject>();
	guiObjectEx2->AddComponent<dae::GuiEx2Component>();
	scene.Add(guiObjectEx2);*/

	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}