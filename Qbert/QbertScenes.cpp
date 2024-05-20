#include "QbertScenes.h"

#include "BlinkingComponent.h"
#include "CoilyMoveComponent.h"
#include "GameObject.h"
#include "imgui.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Minigin.h"
#include "QbertCommand.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"

#include "ScenesState.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"

qbert::SceneStates* qbert::QbertScenes::m_pSceneState = new qbert::StartMenuSceneState{};
bool qbert::QbertScenes::goNext = false;
bool qbert::QbertScenes::gameOver = false;

void qbert::QbertScenes::Init()
{
	m_pSceneState->Enter();
}

void qbert::QbertScenes::LoadQbertLevel()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");

	auto backgroundObject = std::make_unique<dae::GameObject>();

	backgroundObject->AddComponent<dae::ImageComponent>("background.tga", true, 0.0f, 0.0f);
	backgroundObject->AddComponent<dae::ImageComponent>("logo.tga", true, 220.0f, 200.0f);
	backgroundObject->SetLocalPosition(0, 0);
	scene.Add(std::move(backgroundObject));


#pragma region SET_MAP

	constexpr int nbOfRow{ 7 };
	int nbOfTiles{ nbOfRow };
	std::unique_ptr<dae::GameObject> pMapObject{ std::make_unique<dae::GameObject>() };
	pMapObject->SetLocalPosition(250.0f, 300.0f);
	pMapObject->AddComponent<qbert::MapComponent>(nbOfRow);
	float baseTileX{ 0.0f };
	float baseTileY{ 0.0f };

	std::vector<std::unique_ptr<dae::GameObject>> tiles{};


	for (int j{ 0 }; j < nbOfRow; ++j)
	{
		for (int i{ 0 }; i < nbOfTiles; ++i)
		{
			auto tileObject = std::make_unique<dae::GameObject>();
			tileObject->AddComponent<qbert::TileComponent>();
			tileObject->AddComponent<dae::ImageComponent>("qbert/Qbert Cubes.png", true, 0.0f, 0.0f, 3, 6);
			tileObject->SetParent(pMapObject.get(), true);
			tileObject->SetLocalPosition(baseTileX + i * tileObject->GetComponent<dae::ImageComponent>()->GetShape().w, baseTileY);

			pMapObject->GetComponent<qbert::MapComponent>()->AddTile(tileObject->GetComponent<qbert::TileComponent>());
			tiles.emplace_back(std::move(tileObject));
		}

		--nbOfTiles;
		baseTileX += tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w / 2.0f;
		baseTileY -= 3 * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h / 4.0f;
	}

	pMapObject->GetComponent<qbert::MapComponent>()->SetCurrentIndexToLast();



#pragma endregion

	auto playerObject = std::make_unique<dae::GameObject>();
	playerObject->AddComponent<dae::ImageComponent>("qbert/Qbert P1 Spritesheet.png", true, 0.0f, 0.0f, 1, 4);
	playerObject->AddComponent<qbert::QbertMoveComponent>(pMapObject->GetComponent<qbert::MapComponent>());

	qbert::QbertMoveCommand qbertMoveRightCommand{ playerObject.get(),  glm::vec2{1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_D, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveLeftCommand{ playerObject.get(),  glm::vec2{-1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_A, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveTopCommand{ playerObject.get(),  glm::vec2{0,1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_W, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveDownCommand{ playerObject.get(),  glm::vec2{0,-1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_S, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);

	auto bubbleObject = std::make_unique<dae::GameObject>();
	bubbleObject->AddComponent<dae::ImageComponent>("qbert/Qbert Curses.png", false);
	bubbleObject->SetParent(playerObject.get());
	bubbleObject->SetLocalPosition(-15.0f, -35.0f);

	playerObject->GetComponent<qbert::QbertMoveComponent>()->SetBubbleImage(bubbleObject->GetComponent<dae::ImageComponent>());


	auto coilyObject = std::make_unique<dae::GameObject>();
	coilyObject->AddComponent<dae::ImageComponent>("qbert/Coily Spritesheet.png", true, 0.0f, 0.0f, 1, 10, 0, 0);
	coilyObject->AddComponent<qbert::CoilyMoveComponent>(pMapObject->GetComponent<qbert::MapComponent>(), playerObject->GetComponent<qbert::QbertMoveComponent>());


	for (auto& tile : tiles)
	{
		scene.Add(std::move(tile));
	}
	scene.Add(std::move(pMapObject));

	scene.Add(std::move(bubbleObject));
	scene.Add(std::move(playerObject));
	scene.Add(std::move(coilyObject));
}

void qbert::QbertScenes::LoadStartMenu()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartMenu");

	auto titleObject = std::make_unique<dae::GameObject>();
	titleObject->AddComponent<dae::ImageComponent>("qbert/Game_Title.png");

	const glm::vec2 titlePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 8.0f)
	};
	titleObject->SetLocalPosition(titlePos);

	auto font = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 36);
	auto pressSpaceObject = std::make_unique<dae::GameObject>();

	dae::Font actualFont = *font;
	std::string enterString{ "Press space to continue..." };

	pressSpaceObject->AddComponent<dae::TextComponent>(enterString, actualFont);
	pressSpaceObject->AddComponent<qbert::BlinkingComponent>(0.25f);

	const glm::vec2 pressSpacePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(3 * dae::Minigin::GetWindowHeight()) / 4.0f)
	};

	pressSpaceObject->SetLocalPosition(pressSpacePos);
	


	scene.Add(std::move(titleObject));
	scene.Add(std::move(pressSpaceObject));

	qbert::GoNextSceneCommand goNextCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_SPACE, std::make_unique<qbert::GoNextSceneCommand>(goNextCommand), dae::InputType::DOWN);
}

void qbert::QbertScenes::LoadLevelLoading()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartMenu");

	auto loadObject = std::make_unique<dae::GameObject>();
	loadObject->AddComponent<dae::ImageComponent>("qbert/Level_ 01_Title.png");

	loadObject->GetComponent<dae::ImageComponent>()->SetWidth(dae::Minigin::GetWindowWidth());
	loadObject->GetComponent<dae::ImageComponent>()->SetHeight(dae::Minigin::GetWindowHeight());

	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::LOAD), 100.0f);



	scene.Add(std::move(loadObject));
}

void qbert::QbertScenes::Update()
{
	qbert::SceneStates* newState = m_pSceneState->HandleTransitions();
	if (newState)
	{
		m_pSceneState->Exit();
		delete m_pSceneState;
		m_pSceneState = newState;
		m_pSceneState->Enter();
	}

	m_pSceneState->Update();
}
