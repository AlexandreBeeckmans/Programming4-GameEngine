#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameObject.h"

#include "Scene.h"

#include "ImageComponent.h"
#include "RotatingComponent.h"

#include "GuiEx2Component.h"

#include "Controller.h"

#include "QbertCommand.h"

#include "QbertMoveComponent.h"
#include "TileComponent.h"
#include "MapComponent.h"



void InitQbertScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObject = std::make_unique<dae::GameObject>();

	backgroundObject->AddComponent<dae::ImageComponent>("background.tga", 0.0f, 0.0f);
	backgroundObject->AddComponent<dae::ImageComponent>("logo.tga", 220.0f, 200.0f);
	backgroundObject->SetLocalPosition(0, 0);
	scene.Add(std::move(backgroundObject));

#pragma region SET_MAP

	constexpr int nbOfRow{ 7 };
	int nbOfTiles{ nbOfRow };
	std::unique_ptr<dae::GameObject> pMapObject{ std::make_unique<dae::GameObject>() };
	pMapObject->SetLocalPosition(250.0f, 300.0f);
	pMapObject->AddComponent<qbert::MapComponent>();
	float baseTileX{ 0.0f };
	float baseTileY{ 0.0f };

	std::vector<std::unique_ptr<dae::GameObject>> tiles{};


	for (int j{ 0 }; j < nbOfRow; ++j)
	{
		for (int i{ 0 }; i < nbOfTiles; ++i)
		{
			auto tileObject = std::make_unique<dae::GameObject>();
			tileObject->AddComponent<qbert::TileComponent>();
			tileObject->AddComponent<dae::ImageComponent>("qbert/Qbert Cubes.png", 0.0f, 0.0f, 3, 6);
			tileObject->SetParent(pMapObject.get(), true);
			tileObject->SetLocalPosition(baseTileX + i * tileObject->GetComponent<dae::ImageComponent>()->GetShape().w, baseTileY);

			pMapObject->GetComponent<qbert::MapComponent>()->AddTile(tileObject->GetComponent<qbert::TileComponent>());
			tiles.emplace_back(std::move(tileObject));
		}

		--nbOfTiles;
		baseTileX += tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w / 2.0f;
		baseTileY -= 3 * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h / 4.0f;
	}



#pragma endregion

	auto playerObject = std::make_unique<dae::GameObject>();
	playerObject->AddComponent<dae::ImageComponent>("qbert/Qbert P1 Spritesheet.png", 0.0f, 0.0f, 1, 4);
	playerObject->AddComponent<qbert::QbertMoveComponent>(pMapObject->GetComponent<qbert::MapComponent>());

	qbert::QbertMoveCommand qbertMoveRightCommand{ playerObject.get(),  glm::vec2{1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_D, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveLeftCommand{ playerObject.get(),  glm::vec2{-1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_A, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveTopCommand{ playerObject.get(),  glm::vec2{0,1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_W, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveDownCommand{ playerObject.get(),  glm::vec2{0,-1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_S, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);






	for (auto& tile : tiles)
	{
		scene.Add(std::move(tile));
	}
	scene.Add(std::move(pMapObject));


	scene.Add(std::move(playerObject));



}
void Load()
{
	InitQbertScene();
}


int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(Load);
	return 0;
}







//void InitTestScene()
//{
//	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
//
//	auto backgrounObject = std::make_shared<dae::GameObject>();
//
//	backgrounObject->AddComponent<dae::ImageComponent>("background.tga", 0.0f, 0.0f);
//	backgrounObject->AddComponent<dae::ImageComponent>("logo.tga", 220.0f, 200.0f);
//	backgrounObject->SetLocalPosition(0, 0);
//	scene.Add(backgrounObject);
//
//
//	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
//	auto titleObject{ std::make_shared<dae::GameObject>() };
//
//	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", *font.get());
//	titleObject->SetLocalPosition(80, 20);
//	scene.Add(titleObject);
//
//	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
//	auto fpsObject = std::make_shared<dae::GameObject>();
//	fpsObject->AddComponent<dae::RenderFPSComponent>(*fontFps.get());
//	fpsObject->SetLocalPosition(50, 150);
//	scene.Add(fpsObject);
//
//	auto statsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
//
//
//#pragma region KEYBOARDOBJECT
//	//Keyboard object
//	auto keyboardLiveTextObject{ std::make_shared<dae::GameObject>() };
//	keyboardLiveTextObject->AddComponent<dae::TextComponent>("Lives : 3", *statsFont.get());
//	keyboardLiveTextObject->SetLocalPosition(20, 250);
//	scene.Add(keyboardLiveTextObject);
//
//	auto keyboardScoreTextObject{ std::make_shared<dae::GameObject>() };
//	keyboardScoreTextObject->AddComponent<dae::TextComponent>("Score : 0", *statsFont.get());
//	keyboardScoreTextObject->SetLocalPosition(20, 275);
//	scene.Add(keyboardScoreTextObject);
//
//
//	auto keyboardObject = std::make_shared<dae::GameObject>();
//	keyboardObject->AddComponent<dae::ImageComponent>("sprite1.png");
//	keyboardObject->SetLocalPosition(15, 15);
//	keyboardObject->AddComponent<dae::MoveComponent>(10.0f);
//	keyboardObject->AddComponent<dae::HealthComponent>();
//	keyboardObject->AddComponent<dae::ScoreComponent>();
//	keyboardObject->AddComponent<dae::UIComponent>(keyboardScoreTextObject->GetComponent<dae::TextComponent>(), keyboardLiveTextObject->GetComponent<dae::TextComponent>());
//
//	dae::InputManager::GetInstance().SetMoveKeyboardCommandActor(keyboardObject.get());
//
//	dae::Die keyboardDieCommand{ keyboardObject.get() };
//	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_Z, std::make_unique<dae::Die>(keyboardDieCommand), dae::InputType::DOWN);
//
//	dae::Score keyboardScoreCommand{ keyboardObject.get() };
//	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_X, std::make_unique<dae::Score>(keyboardScoreCommand), dae::InputType::DOWN);
//
//
//	scene.Add(keyboardObject);
//#pragma endregion
//
//#pragma region GAMEPADOBJECT
//	//Gamepad Object
//
//
//	auto gamePadLiveTextObject{ std::make_shared<dae::GameObject>() };
//	gamePadLiveTextObject->AddComponent<dae::TextComponent>("Lives : 3", *statsFont.get());
//	gamePadLiveTextObject->SetLocalPosition(20, 200);
//	scene.Add(gamePadLiveTextObject);
//
//	auto gamePadScoreTextObject{ std::make_shared<dae::GameObject>() };
//	gamePadScoreTextObject->AddComponent<dae::TextComponent>("Score : 0", *statsFont.get());
//	gamePadScoreTextObject->SetLocalPosition(20, 225);
//	scene.Add(gamePadScoreTextObject);
//
//
//	auto gamePadPlayer = std::make_shared<dae::GameObject>();
//	gamePadPlayer->AddComponent<dae::ImageComponent>("sprite2.png");
//	gamePadPlayer->SetLocalPosition(150, 15);
//	gamePadPlayer->AddComponent<dae::MoveComponent>(2 * keyboardObject->GetComponent<dae::MoveComponent>()->GetSpeed());
//	gamePadPlayer->AddComponent<dae::HealthComponent>();
//	gamePadPlayer->AddComponent<dae::ScoreComponent>();
//	gamePadPlayer->AddComponent<dae::UIComponent>(gamePadScoreTextObject->GetComponent<dae::TextComponent>(), gamePadLiveTextObject->GetComponent<dae::TextComponent>());
//
//	std::unique_ptr<dae::GamepadController> gamepadController{ std::make_unique<dae::GamepadController>() };
//	gamepadController->BindMoveInput(gamePadPlayer.get());
//
//	dae::Die gamepadDieCommand{ gamePadPlayer.get() };
//	gamepadController->Bind(XINPUT_GAMEPAD_A, std::make_unique<dae::Die>(gamepadDieCommand), dae::InputType::DOWN);
//
//	dae::Score gamepadScoreCommand{ gamePadPlayer.get() };
//	gamepadController->Bind(XINPUT_GAMEPAD_X, std::make_unique<dae::Score>(gamepadScoreCommand), dae::InputType::DOWN);
//
//
//	dae::InputManager::GetInstance().AddController(std::move(gamepadController));
//
//
//	scene.Add(gamePadPlayer);
//#pragma endregion
//
//
//	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
//
//	auto inputText1Object{ std::make_shared<dae::GameObject>() };
//	inputText1Object->AddComponent<dae::TextComponent>("Use WASD to move orange QBert, W to remove life, X to earn points", *inputFont.get());
//	inputText1Object->SetLocalPosition(20, 100);
//	scene.Add(inputText1Object);
//
//	auto inputText2Object{ std::make_shared<dae::GameObject>() };
//	inputText2Object->AddComponent<dae::TextComponent>("Use D-Pad to move yellow QBert, A to remove life, X to earn points", *inputFont.get());
//	inputText2Object->SetLocalPosition(20, 125);
//	scene.Add(inputText2Object);
//
//}