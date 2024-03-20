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

	std::unique_ptr<dae::GamepadController> gamepadController{std::make_unique<dae::GamepadController>()};
	gamepadController->BindMoveInput(childObject.get());
	dae::InputManager::GetInstance().AddController(std::move(gamepadController));

	scene.Add(childObject);

	auto centerOfRotationObject{ std::make_shared<dae::GameObject>() };
	centerOfRotationObject->SetLocalPosition(200, 300);
	scene.Add(centerOfRotationObject);
	
	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	auto inputText1Object{ std::make_shared<dae::GameObject>() };
	inputText1Object->AddComponent<dae::TextComponent>("Use WASD to move orange QBert", *inputFont.get());
	inputText1Object->SetLocalPosition(20, 100);
	scene.Add(inputText1Object);

	auto inputText2Object{ std::make_shared<dae::GameObject>() };
	inputText2Object->AddComponent<dae::TextComponent>("Use D-Pad to move yellow QBert", *inputFont.get());
	inputText2Object->SetLocalPosition(20, 125);
	scene.Add(inputText2Object);



	auto statsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto liveTextObject{ std::make_shared<dae::GameObject>() };
	liveTextObject->AddComponent<dae::TextComponent>("Lives : 3", *statsFont.get());
	liveTextObject->SetLocalPosition(20, 200);
	scene.Add(liveTextObject);

	auto scoreTextObject{ std::make_shared<dae::GameObject>() };
	scoreTextObject->AddComponent<dae::TextComponent>("Score : 0", *statsFont.get());
	scoreTextObject->SetLocalPosition(20, 225);
	scene.Add(scoreTextObject);



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