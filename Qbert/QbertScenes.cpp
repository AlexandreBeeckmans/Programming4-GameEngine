
#include <windows.h>
#include <Xinput.h>

#include "QbertScenes.h"

#include "AnimatorComponent.h"
#include "BlinkingComponent.h"
#include "ChangeToUIComponent.h"

#include "QbertFSMManagerComponent.h"
#include "CoilyFSMManagerComponent.h"


#include "DiscComponent.h"
#include "FallComponent.h"
#include "BubbleManagerComponent.h"
#include "FollowPlayerComponent.h"
#include "KillableComponent.h"
#include "GridMoveComponent.h"

#include "KillerComponent.h"
#include "CoilyAnimatorComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthUIComponent.h"
#include "imgui.h"
#include "InputDirectionComponent.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Minigin.h"
#include "QbertCommand.h"
#include "QbertJumpAnimatorComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"

#include "ScenesState.h"
#include "ScoreComponent.h"
#include "ScoreUIComponent.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"
#include "TileActivatorComponent.h"

std::unique_ptr<qbert::SceneStates> qbert::QbertScenes::m_pSceneState = std::make_unique<qbert::StartMenuSceneState>(qbert::StartMenuSceneState{});
const float qbert::QbertScenes::m_LevelScale = 2.0f;

bool qbert::QbertScenes::goNext = false;
bool qbert::QbertScenes::gameOver = false;

void qbert::QbertScenes::Init()
{
	m_pSceneState->Enter();
}

void qbert::QbertScenes::LoadQbertLevel(const int level, const int round)
{
	dae::ImageComponent::SetSpriteScale(m_LevelScale);
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

	pMapObject->AddComponent<qbert::MapComponent>(nbOfRow);
	float baseTileX{ 0.0f };
	float baseTileY{ 0.0f };

	std::vector<std::unique_ptr<dae::GameObject>> tiles{};


	for (int j{ 0 }; j < nbOfRow; ++j)
	{
		for (int i{ 0 }; i < nbOfTiles; ++i)
		{
			auto tileObject = std::make_unique<dae::GameObject>();
			tileObject->AddComponent<qbert::TileComponent>(level%2 + 1, level >= 2);
			tileObject->AddComponent<dae::ImageComponent>("qbert/Qbert Cubes.png", true, 0.0f, 0.0f, 3, 6, 0, round);
			tileObject->AddComponent<dae::AnimatorComponent>(false, 0.1f, 1,3,round,0);

			tileObject->SetParent(pMapObject.get(), true);
			tileObject->SetLocalPosition(baseTileX + i * tileObject->GetComponent<dae::ImageComponent>()->GetShape().w, baseTileY);

			pMapObject->GetComponent<qbert::MapComponent>()->AddTile(tileObject->GetComponent<qbert::TileComponent>());
			tiles.emplace_back(std::move(tileObject));
		}

		--nbOfTiles;
		baseTileX += tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w / 2.0f;
		baseTileY -= 3 * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h / 4.0f;
	}

	const glm::vec2 mapPosition
	{
		static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(nbOfRow * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f,
		static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f + static_cast<float>(nbOfRow * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h) / 4.0f
	};
	pMapObject->SetLocalPosition(mapPosition);



#pragma endregion

	auto playerObject = CreatePlayer(pMapObject->GetComponent<MapComponent>());
	auto bubbleObject = CreateBubble(playerObject.get());

	playerObject->GetComponent<qbert::BubbleManagerComponent>()->SetBubbleImage(bubbleObject->GetComponent<dae::ImageComponent>());


	auto coilyObject = CreateCoily(playerObject.get(), pMapObject->GetComponent<MapComponent>());
	

#pragma region DISC
	auto leftDiscObject = std::make_unique<dae::GameObject>();
	leftDiscObject->SetLocalPosition(150, 150);

	leftDiscObject->AddComponent<dae::ImageComponent>("qbert/Disk_Spritesheet.png", true, 0.0f, 0.0f, 1, 30, 0, 5 * round);
	leftDiscObject->AddComponent<dae::AnimatorComponent>(true, 0.25f, 4, 1, 5 * round, 0);
	leftDiscObject->AddComponent<qbert::DiscComponent>(pMapObject->GetComponent<qbert::MapComponent>());


	auto rightDiscObject = std::make_unique<dae::GameObject>();
	rightDiscObject->SetLocalPosition(150, 150);

	rightDiscObject->AddComponent<dae::ImageComponent>("qbert/Disk_Spritesheet.png", true, 0.0f, 0.0f, 1, 30, 0, 5 * round);
	rightDiscObject->AddComponent<dae::AnimatorComponent>(true, 0.25f, 4, 1, 5 * round, 0);
	rightDiscObject->AddComponent<qbert::DiscComponent>(pMapObject->GetComponent<qbert::MapComponent>(), false);

	pMapObject->GetComponent<MapComponent>()->AddDisc(leftDiscObject->GetComponent<DiscComponent>());
	pMapObject->GetComponent<MapComponent>()->AddDisc(rightDiscObject->GetComponent<DiscComponent>());

#pragma endregion

#pragma region UI
	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 24);

	//Score
	auto scoreUIObject = std::make_unique<dae::GameObject>();
	scoreUIObject->AddComponent<dae::TextComponent>("Saucisse", *scoreFont);
	

	dae::TextComponent* scoreTextComponent = scoreUIObject->GetComponent<dae::TextComponent>();
	scoreTextComponent->SetRelativePosition(25, 25);
	scoreTextComponent->SetColor({ 255,165,0, 255 });

	scoreUIObject->AddComponent<qbert::ScoreUIComponent>(scoreTextComponent, 0);
	scoreUIObject->GetComponent<qbert::ScoreUIComponent>()->SetScoreComponent(playerObject->GetComponent<dae::ScoreComponent>());

	playerObject->GetComponent<dae::ScoreComponent>()->InitObserver(scoreUIObject->GetComponent<ScoreUIComponent>());

	//NextTile
	auto changeToUIObject = std::make_unique<dae::GameObject>();
	changeToUIObject->SetLocalPosition(0, 45);

	//main text
	changeToUIObject->AddComponent<dae::TextComponent>("CHANGE TO:", *scoreFont);
	changeToUIObject->GetComponent<dae::TextComponent>()->SetColor({ 255,0,0,255 });

	
	std::vector<dae::ImageComponent*> pArrowComponents{};
	//2 arrows left
	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow.png", true, 15.0f, 20.0f);
	pArrowComponents.push_back( {changeToUIObject->GetComponent<dae::ImageComponent>(1) });

	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow.png", true, 40.0f, 20.0f);
	pArrowComponents.push_back({ changeToUIObject->GetComponent<dae::ImageComponent>(2) });

	//middle tile
	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/Color_Icons_Spritesheet.png", true,  55.0f, 20.0f, 2, 6, level%2, round);

	//2 arrows right
	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow_Left.png", true, 85.0f, 20.0f);
	pArrowComponents.push_back({ changeToUIObject->GetComponent<dae::ImageComponent>(4) });

	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow_Left.png", true, 110.0f, 20.0f);
	pArrowComponents.push_back({ changeToUIObject->GetComponent<dae::ImageComponent>(5) });

	for (auto arrow : pArrowComponents)
	{
		arrow->SetWidth(15);
		arrow->SetHeight(25);
	}

	changeToUIObject->AddComponent<qbert::ChangeToUIComponent>(pArrowComponents);

	




	//Level and Round
	auto levelUIObject = std::make_unique<dae::GameObject>();
	levelUIObject->AddComponent<dae::TextComponent>("LEVEL :", *scoreFont);
	levelUIObject->GetComponent<dae::TextComponent>(0)->SetColor({ 0, 255, 0, 255 });

	levelUIObject->AddComponent<dae::TextComponent>(std::to_string(level + 1), *scoreFont);
	levelUIObject->GetComponent<dae::TextComponent>(1)->SetRelativePosition(115, 0);
	levelUIObject->GetComponent<dae::TextComponent>(1)->SetColor({ 255, 165, 0, 255 });

	levelUIObject->AddComponent<dae::TextComponent>("ROUND :", *scoreFont);
	levelUIObject->GetComponent<dae::TextComponent>(2)->SetRelativePosition(0, 25);
	levelUIObject->GetComponent<dae::TextComponent>(2)->SetColor({ 0, 0, 255, 255 });

	levelUIObject->AddComponent<dae::TextComponent>(std::to_string(round + 1), *scoreFont);
	levelUIObject->GetComponent<dae::TextComponent>(3)->SetRelativePosition(115, 25);
	levelUIObject->GetComponent<dae::TextComponent>(3)->SetColor({ 255, 165, 0, 255 });

	levelUIObject->SetLocalPosition(static_cast<float>(dae::Minigin::GetWindowWidth()) - 150.0f, 10.0f);
	

	//Lives
	auto livesUIObject = std::make_unique<dae::GameObject>();
	livesUIObject->AddComponent<dae::ImageComponent>("qbert/Lives_UI.png");
	livesUIObject->SetLocalPosition(0, 150);
	livesUIObject->AddComponent<HealthUIComponent>(livesUIObject->GetComponent<dae::ImageComponent>());

	livesUIObject->GetComponent<qbert::HealthUIComponent>()->SetHealthComponent(playerObject->GetComponent<dae::HealthComponent>());
	playerObject->GetComponent<dae::HealthComponent>()->AddObserver(livesUIObject->GetComponent<qbert::HealthUIComponent>());

#pragma endregion


	//Add everything to the scene
	scene.Add(std::move(livesUIObject));
	scene.Add(std::move(levelUIObject));
	scene.Add(std::move(changeToUIObject));
	scene.Add(std::move(scoreUIObject));

	

	for (auto& tile : tiles)
	{
		scene.Add(std::move(tile));
	}
	scene.Add(std::move(pMapObject));

	scene.Add(std::move(leftDiscObject));
	scene.Add(std::move(rightDiscObject));

	scene.Add(std::move(bubbleObject));
	scene.Add(std::move(playerObject));
	scene.Add(std::move(coilyObject));



}

void qbert::QbertScenes::LoadStartMenu()
{
	dae::ImageComponent::SetSpriteScale(1.0f);
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

void qbert::QbertScenes::LoadLevelLoading(const int level)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartMenu");

	auto loadObject = std::make_unique<dae::GameObject>();
	loadObject->AddComponent<dae::ImageComponent>("qbert/Level_" + std::to_string(level + 1) + "_Title.png");

	loadObject->GetComponent<dae::ImageComponent>()->SetWidth(dae::Minigin::GetWindowWidth());
	loadObject->GetComponent<dae::ImageComponent>()->SetHeight(dae::Minigin::GetWindowHeight());

	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::LOAD), 100.0f);



	scene.Add(std::move(loadObject));
}

void qbert::QbertScenes::Update()
{
	std::unique_ptr<SceneStates> pNewState = m_pSceneState->HandleTransitions();
	if (pNewState)
	{
		m_pSceneState->Exit();
		//delete m_pSceneState;
		m_pSceneState = std::move(pNewState);
		m_pSceneState->Enter();
	}

	m_pSceneState->Update();
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreatePlayer(MapComponent* pMapComponent)
{
	std::unique_ptr<dae::GameObject> playerObject = std::make_unique<dae::GameObject>();

	playerObject->AddComponent<dae::ImageComponent>("qbert/Qbert P1 Spritesheet.png", true, 0.0f, 0.0f, 1, 4);
	playerObject->AddComponent<qbert::QbertFSMManagerComponent>();
	playerObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	playerObject->GetComponent<qbert::GridMoveComponent>()->SetCurrentIndexToTop();
	playerObject->AddComponent<qbert::FallComponent>();
	playerObject->AddComponent<qbert::InputDirectionComponent>();
	playerObject->AddComponent<qbert::BubbleManagerComponent>();
	playerObject->AddComponent<qbert::KillableComponent>();
	playerObject->AddComponent<qbert::TileActivatorComponent>(pMapComponent);
	playerObject->AddComponent<qbert::QbertJumpAnimatorComponent>();

	playerObject->AddComponent<dae::ScoreComponent>();
	playerObject->AddComponent<dae::HealthComponent>();


	std::unique_ptr<dae::GamepadController> gamepadController{ std::make_unique<dae::GamepadController>() };

	qbert::QbertMoveCommand qbertMoveRightCommand{ playerObject.get(),  glm::vec2{1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_D, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveLeftCommand{ playerObject.get(),  glm::vec2{-1,0} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_A, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveTopCommand{ playerObject.get(),  glm::vec2{0,1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_W, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_UP, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);

	qbert::QbertMoveCommand qbertMoveDownCommand{ playerObject.get(),  glm::vec2{0,-1} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_S, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);

	dae::InputManager::GetInstance().AddController(std::move(gamepadController));

	return playerObject;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateBubble(dae::GameObject* pPlayerObject)
{
	std::unique_ptr<dae::GameObject> bubbleObject{ std::make_unique<dae::GameObject>() };
	bubbleObject->AddComponent<dae::ImageComponent>("qbert/Qbert Curses.png", false);
	bubbleObject->SetParent(pPlayerObject);
	bubbleObject->SetLocalPosition(-15.0f, -35.0f);

	return bubbleObject;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateCoily(dae::GameObject* pPlayerObject, MapComponent* pMapComponent)
{
	std::unique_ptr<dae::GameObject> coilyObject = std::make_unique<dae::GameObject>();
	coilyObject->AddComponent<dae::ImageComponent>("qbert/Coily Spritesheet.png", true, 0.0f, 0.0f, 1, 10, 0, 0);
	coilyObject->AddComponent<qbert::CoilyFSMManagerComponent>();
	coilyObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	coilyObject->AddComponent<qbert::FallComponent>();
	coilyObject->AddComponent<qbert::FollowPlayerComponent>(pPlayerObject->GetComponent<GridMoveComponent>(), pMapComponent);
	coilyObject->AddComponent<qbert::KillerComponent>(pPlayerObject);
	coilyObject->AddComponent<qbert::CoilyAnimatorComponent>();

	return coilyObject;
}
