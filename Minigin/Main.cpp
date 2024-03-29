#include <SDL.h>
#include <memory>

#include <windows.h>
#include <Xinput.h>
#include <steam_api.h>

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
#include "HealthComponent.h"
#include "ScoreComponent.h"

#include "GuiEx1Component.h"
#include "GuiEx2Component.h"

#include "Font.h"

#include "Controller.h"
#include "Observer.h"

#include "Command.h"

#include "Achievements.h"


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

	auto statsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);


#pragma region KEYBOARDOBJECT
	//Keyboard object
	auto keyboardLiveTextObject{ std::make_shared<dae::GameObject>() };
	keyboardLiveTextObject->AddComponent<dae::TextComponent>("Lives : 3", *statsFont.get());
	keyboardLiveTextObject->SetLocalPosition(20, 250);
	scene.Add(keyboardLiveTextObject);

	auto keyboardScoreTextObject{ std::make_shared<dae::GameObject>() };
	keyboardScoreTextObject->AddComponent<dae::TextComponent>("Score : 0", *statsFont.get());
	keyboardScoreTextObject->SetLocalPosition(20, 275);
	scene.Add(keyboardScoreTextObject);



	std::unique_ptr<dae::GameActionsObserver> keyboardObjectObserver{ std::make_unique<dae::GameActionsObserver>() };


	auto keyboardObject = std::make_shared<dae::GameObject>(std::move(keyboardObjectObserver));
	keyboardObject->AddComponent<dae::ImageComponent>("sprite1.png");
	keyboardObject->SetLocalPosition(15, 15);
	keyboardObject->AddComponent<dae::MoveComponent>();
	keyboardObject->AddComponent<dae::HealthComponent>();
	keyboardObject->AddComponent<dae::ScoreComponent>();

	dae::InputManager::GetInstance().SetMoveKeyboardCommandActor(keyboardObject.get());

	dae::Die keyboardDieCommand{ keyboardObject.get(), keyboardLiveTextObject->GetComponent <dae::TextComponent>() };
	dae::InputManager::GetInstance().BindKeyboardInput(SDLK_z, std::make_unique<dae::Die>(keyboardDieCommand));

	dae::Score keyboardScoreCommand{ keyboardObject.get(), keyboardScoreTextObject->GetComponent<dae::TextComponent>() };
	dae::InputManager::GetInstance().BindKeyboardInput(SDLK_x, std::make_unique<dae::Score>(keyboardScoreCommand));


	scene.Add(keyboardObject);
#pragma endregion

	
	




#pragma region GAMEPADOBJECT
	//Gamepad Object
	

	auto gamePadLiveTextObject{ std::make_shared<dae::GameObject>() };
	gamePadLiveTextObject->AddComponent<dae::TextComponent>("Lives : 3", *statsFont.get());
	gamePadLiveTextObject->SetLocalPosition(20, 200);
	scene.Add(gamePadLiveTextObject);

	auto gamePadScoreTextObject{ std::make_shared<dae::GameObject>() };
	gamePadScoreTextObject->AddComponent<dae::TextComponent>("Score : 0", *statsFont.get());
	gamePadScoreTextObject->SetLocalPosition(20, 225);
	scene.Add(gamePadScoreTextObject);



	std::unique_ptr<dae::GameActionsObserver> gamepadObjectObserver{ std::make_unique<dae::GameActionsObserver>() };

	auto gamePadPlayer = std::make_shared<dae::GameObject>(std::move(gamepadObjectObserver));
	gamePadPlayer->AddComponent<dae::ImageComponent>("sprite2.png");
	gamePadPlayer->SetLocalPosition(150, 15);
	gamePadPlayer->AddComponent<dae::MoveComponent>(2 * keyboardObject->GetComponent<dae::MoveComponent>()->GetSpeed());
	gamePadPlayer->AddComponent<dae::HealthComponent>();
	gamePadPlayer->AddComponent<dae::ScoreComponent>();

	std::unique_ptr<dae::GamepadController> gamepadController{std::make_unique<dae::GamepadController>()};
	gamepadController->BindMoveInput(gamePadPlayer.get());

	dae::Die gamepadDieCommand{ gamePadPlayer.get(), gamePadLiveTextObject->GetComponent<dae::TextComponent>() };
	gamepadController->Bind(XINPUT_GAMEPAD_A, std::make_unique<dae::Die>(gamepadDieCommand));

	dae::Score gamepadScoreCommand{ gamePadPlayer.get(), gamePadScoreTextObject->GetComponent<dae::TextComponent>() };
	gamepadController->Bind(XINPUT_GAMEPAD_X, std::make_unique<dae::Score>(gamepadScoreCommand));


	dae::InputManager::GetInstance().AddController(std::move(gamepadController));

	
	scene.Add(gamePadPlayer);
#pragma endregion

	
	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	auto inputText1Object{ std::make_shared<dae::GameObject>() };
	inputText1Object->AddComponent<dae::TextComponent>("Use WASD to move orange QBert, Z to remove life, X to earn points", *inputFont.get());
	inputText1Object->SetLocalPosition(20, 100);
	scene.Add(inputText1Object);

	auto inputText2Object{ std::make_shared<dae::GameObject>() };
	inputText2Object->AddComponent<dae::TextComponent>("Use D-Pad to move yellow QBert, A to remove life, X to earn points", *inputFont.get());
	inputText2Object->SetLocalPosition(20, 125);
	scene.Add(inputText2Object);

	
}

int main(int, char*[]) 
{
	//Setup Steam
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;

	CSteamAchievements::g_SteamAchievements = new CSteamAchievements{ g_Achievements, 4 };

	dae::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
	if (CSteamAchievements::g_SteamAchievements)
		delete CSteamAchievements::g_SteamAchievements;


    return 0;
}