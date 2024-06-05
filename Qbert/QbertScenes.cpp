
#include <windows.h>
#include <Xinput.h>

#include "QbertScenes.h"

#include "AnimatorComponent.h"
#include "BlinkingComponent.h"
#include "ChangeToUIComponent.h"

#include "PlayerState.h"
#include "CoilyState.h"
#include "SlickState.h"


#include "DiscComponent.h"
#include "FallComponent.h"
#include "BubbleManagerComponent.h"
#include "FollowPlayerComponent.h"
#include "KillableComponent.h"
#include "GridMoveComponent.h"

#include "KillerComponent.h"
#include "CoilyAnimatorComponent.h"
#include "DeadFallComponent.h"
#include "FSMManagerComponent.hpp"
#include "SlickAnimatorComponent.h"

#include "TileDeactivatorComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthUIComponent.h"
#include "imgui.h"
#include "InputDirectionComponent.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "MapComponent.h"
#include "Minigin.h"
#include "PlayerKillableComponent.h"
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
#include "SlickDirection.h"
#include "SoundTypes.h"
#include "TileActivatorComponent.h"

std::unique_ptr<qbert::SceneStates> qbert::QbertScenes::m_pSceneState = std::make_unique<qbert::StartMenuSceneState>(qbert::StartMenuSceneState{});
const float qbert::QbertScenes::m_LevelScale = 2.0f;
int qbert::QbertScenes::nbPlayer{};

bool qbert::QbertScenes::goNext = false;
bool qbert::QbertScenes::gameOver = false;

void qbert::QbertScenes::Init()
{
	m_pSceneState->Enter();
}

void qbert::QbertScenes::LoadQbertLevel(const int level, const int round, const int nbPlayerLevel, const bool isVersus)
{
	LevelInfo levelInfo{ LevelLoader::GetInstance().LoadLevel(level + 1, round + 1) };

	SetNbPlayer(nbPlayerLevel);
	dae::ImageComponent::SetSpriteScale(m_LevelScale);
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level" + std::to_string(level) + "Round" + std::to_string(round));

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

	std::vector<std::unique_ptr<dae::GameObject>> playerObjects{};
	std::vector<std::unique_ptr<dae::GameObject>> bubbleObjects{};
	for(int i{0}; i < nbPlayerLevel; ++i)
	{
		playerObjects.push_back(CreatePlayer(i + 1, pMapObject->GetComponent<MapComponent>()));
		bubbleObjects.push_back(CreateBubble(playerObjects[i].get()));
		playerObjects[i]->GetComponent<qbert::BubbleManagerComponent>()->SetBubbleImage(bubbleObjects[i]->GetComponent<dae::ImageComponent>());
	}

	//reposition if multiple players
	if(nbPlayerLevel > 1)
	{
		playerObjects[0]->GetComponent<GridMoveComponent>()->SetCurrentIndex(0);
		playerObjects[1]->GetComponent<GridMoveComponent>()->SetCurrentIndex(nbOfRow - 1);
	}

	

	

	std::vector<std::unique_ptr<dae::GameObject>> coilyObjects{};
	for(int i{0}; i < levelInfo.nbCoily; ++i)
	{
		coilyObjects.push_back(CreateCoily(i, &playerObjects, pMapObject->GetComponent<MapComponent>(), isVersus));
	}

	std::vector<std::unique_ptr<dae::GameObject>> slickObjects{};

	for (int i{ 0 }; i < levelInfo.nbSlick; ++i)
	{
		slickObjects.push_back(CreateSlick(static_cast<bool>(i%2), &playerObjects, pMapObject->GetComponent<MapComponent>()));
	}
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
#pragma region SCORE1_OBJECT
	auto scoreUIObject = std::make_unique<dae::GameObject>();
	scoreUIObject->AddComponent<dae::TextComponent>("Saucisse", *scoreFont);
	

	dae::TextComponent* scoreTextComponent = scoreUIObject->GetComponent<dae::TextComponent>();
	scoreTextComponent->SetRelativePosition(25, 25);
	scoreTextComponent->SetColor({ 255,165,0, 255 });

	scoreUIObject->AddComponent<qbert::ScoreUIComponent>(scoreTextComponent, 0);
	scoreUIObject->GetComponent<qbert::ScoreUIComponent>()->SetScoreComponent(playerObjects[0]->GetComponent<dae::ScoreComponent>());

	playerObjects[0]->GetComponent<dae::ScoreComponent>()->InitObserver(scoreUIObject->GetComponent<ScoreUIComponent>());
#pragma endregion

#pragma region SCORE2_OBJECT
	if(nbPlayerLevel > 1)
	{
		auto scoreUI2Object = std::make_unique<dae::GameObject>();
		scoreUI2Object->AddComponent<dae::TextComponent>("Saucisse", *scoreFont);


		dae::TextComponent* scoreText2Component = scoreUI2Object->GetComponent<dae::TextComponent>();
		scoreText2Component->SetRelativePosition(25, 25);
		scoreText2Component->SetColor({ 255,165,0, 255 });

		scoreUI2Object->AddComponent<qbert::ScoreUIComponent>(scoreText2Component, 1);
		scoreUI2Object->GetComponent<qbert::ScoreUIComponent>()->SetScoreComponent(playerObjects[1]->GetComponent<dae::ScoreComponent>());


		playerObjects[1]->GetComponent<dae::ScoreComponent>()->InitObserver(scoreUI2Object->GetComponent<ScoreUIComponent>());

		scoreUI2Object->Translate(glm::vec2{ 100,0 });
		scene.Add(std::move(scoreUI2Object));
	}
#pragma endregion

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
#pragma region LIVE1_OBJECT
	auto livesUIObject = std::make_unique<dae::GameObject>();
	livesUIObject->AddComponent<dae::ImageComponent>("qbert/Lives_UI_P1.png");
	livesUIObject->SetLocalPosition(0, 150);
	livesUIObject->AddComponent<HealthUIComponent>(livesUIObject->GetComponent<dae::ImageComponent>());

	livesUIObject->GetComponent<qbert::HealthUIComponent>()->SetHealthComponent(playerObjects[0]->GetComponent<dae::HealthComponent>());
	playerObjects[0]->GetComponent<dae::HealthComponent>()->AddObserver(livesUIObject->GetComponent<qbert::HealthUIComponent>());
#pragma endregion

#pragma region LIVE2_OBJECT
	if(nbPlayerLevel > 1)
	{
		auto lives2UIObject = std::make_unique<dae::GameObject>();
		lives2UIObject->AddComponent<dae::ImageComponent>("qbert/Lives_UI_P2.png");
		lives2UIObject->SetLocalPosition(0, 150);
		lives2UIObject->AddComponent<HealthUIComponent>(lives2UIObject->GetComponent<dae::ImageComponent>());

		lives2UIObject->GetComponent<qbert::HealthUIComponent>()->SetHealthComponent(playerObjects[1]->GetComponent<dae::HealthComponent>());
		playerObjects[1]->GetComponent<dae::HealthComponent>()->AddObserver(lives2UIObject->GetComponent<qbert::HealthUIComponent>());

		lives2UIObject->Translate(glm::vec2{ 50,0 });
		scene.Add(std::move(lives2UIObject));
	}
	
#pragma endregion

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

	for (auto& bubble : bubbleObjects)
	{
		scene.Add(std::move(bubble));
	}

	for (auto& player : playerObjects)
	{
		scene.Add(std::move(player));
	}

	for (auto& coily : coilyObjects)
	{
		scene.Add(std::move(coily));
	}

	for (auto& slick : slickObjects)
	{
		scene.Add(std::move(slick));
	}
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
	auto soloObject = std::make_unique<dae::GameObject>();
	auto coopObject = std::make_unique<dae::GameObject>();
	auto versusObject = std::make_unique<dae::GameObject>();

	dae::Font actualFont = *font;
	std::string enterString{ "Press space to continue..." };
	std::string soloString{ "Solo  Mode" };
	std::string coopString{ "Coop Mode" };
	std::string versusString{ "Versus Mode" };

	pressSpaceObject->AddComponent<dae::TextComponent>(enterString, actualFont);
	pressSpaceObject->AddComponent<qbert::BlinkingComponent>(0.25f);

	soloObject->AddComponent<dae::TextComponent>(soloString, actualFont);
	coopObject->AddComponent<dae::TextComponent>(coopString, actualFont);
	versusObject->AddComponent<dae::TextComponent>(versusString, actualFont);

	const glm::vec2 pressSpacePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(pressSpaceObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) - static_cast<float>(pressSpaceObject->GetComponent<dae::ImageComponent>()->GetShape().h))
	};
	pressSpaceObject->SetLocalPosition(pressSpacePos);

	constexpr float titleOffset{ 100.f };
	constexpr float titleDiscplacement{ 100.0f };
	const glm::vec2 soloPos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(soloObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().y + titleObject->GetComponent<dae::ImageComponent>()->GetShape().h) + titleOffset + 0 * titleDiscplacement)
	};
	soloObject->SetLocalPosition(soloPos);

	const glm::vec2 coopPos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(coopObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().y + titleObject->GetComponent<dae::ImageComponent>()->GetShape().h) + titleOffset +  1 * titleDiscplacement)
	};
	coopObject->SetLocalPosition(coopPos);

	const glm::vec2 versusPos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(versusObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().y + titleObject->GetComponent<dae::ImageComponent>()->GetShape().h) + titleOffset + 2 * titleDiscplacement)
	};
	versusObject->SetLocalPosition(versusPos);


	//cursor
	auto cursorObject{ std::make_unique<dae::GameObject>() };
	cursorObject->AddComponent<dae::ImageComponent>("qbert/Selection_Arrow.png");
	cursorObject->GetComponent<dae::ImageComponent>()->SetWidth(10);
	cursorObject->GetComponent<dae::ImageComponent>()->SetHeight(25);

	const glm::vec2 cursorPos
	{
		static_cast<int>(soloObject->GetWorldPosition().x - static_cast<float>(cursorObject->GetComponent<dae::ImageComponent>()->GetShape().w) - 50),
		soloObject->GetWorldPosition().y
	};
	cursorObject->SetLocalPosition(cursorPos);
	
	qbert::SelectCommand selectDownCommand{ cursorObject.get(), 1, titleDiscplacement };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_DOWN, std::make_unique<qbert::SelectCommand>(selectDownCommand), dae::InputType::DOWN);

	qbert::SelectCommand selectUpCommand{ cursorObject.get(), -1, titleDiscplacement };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_UP, std::make_unique<qbert::SelectCommand>(selectUpCommand), dae::InputType::DOWN);

	scene.Add(std::move(titleObject));
	scene.Add(std::move(pressSpaceObject));
	scene.Add(std::move(soloObject));
	scene.Add(std::move(coopObject));
	scene.Add(std::move(versusObject));
	scene.Add(std::move(cursorObject));

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
		m_pSceneState = std::move(pNewState);
		m_pSceneState->Enter();
	}

	m_pSceneState->Update();
}

void qbert::QbertScenes::SetNbPlayer(const int nbPlayers)
{
	nbPlayer = nbPlayers;
}

void qbert::QbertScenes::ReducePlayer()
{
	--nbPlayer;
}

bool qbert::QbertScenes::AreAllPlayersDead()
{
	return nbPlayer <= 0;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreatePlayer(const int playerNb, MapComponent* pMapComponent)
{
	std::unique_ptr<dae::GameObject> playerObject = std::make_unique<dae::GameObject>();

	playerObject->AddComponent<dae::ImageComponent>("qbert/Qbert P" + std::to_string(playerNb) +" Spritesheet.png", true, 0.0f, 0.0f, 1, 4);
	playerObject->AddComponent<dae::FSMManagerComponent<PlayerState, WaitingState>>();
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
	qbert::QbertMoveCommand qbertMoveLeftCommand{ playerObject.get(),  glm::vec2{-1,0} };
	qbert::QbertMoveCommand qbertMoveTopCommand{ playerObject.get(),  glm::vec2{0,1} };
	qbert::QbertMoveCommand qbertMoveDownCommand{ playerObject.get(),  glm::vec2{0,-1} };

	if(playerNb == 1)
	{
		dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_D, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);
		dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_A, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);
		dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_W, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);
		dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_S, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);
	}
	
	
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);
	gamepadController->Bind(XINPUT_GAMEPAD_DPAD_UP, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);
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

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateCoily(const int coilyNb,  std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent, const bool isVersus)
{
	std::unique_ptr<dae::GameObject> coilyObject = std::make_unique<dae::GameObject>();
	coilyObject->AddComponent<dae::ImageComponent>("qbert/Coily Spritesheet.png", true, 0.0f, 0.0f, 1, 10, 0, 0);
	coilyObject->AddComponent<dae::FSMManagerComponent<CoilyState, CoilyPreparingState>>();
	coilyObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	coilyObject->AddComponent<qbert::FallComponent>();
	coilyObject->AddComponent<qbert::KillerComponent>(pPlayerObjects);
	coilyObject->AddComponent<qbert::CoilyAnimatorComponent>();

	coilyObject->GetComponent<qbert::GridMoveComponent>()->SetCurrentIndex(coilyNb * 6);

	if(isVersus && coilyNb == 0)
	{
		coilyObject->AddComponent<qbert::InputDirectionComponent>();
		std::unique_ptr<dae::GamepadController> gamepadController{ std::make_unique<dae::GamepadController>() };

		qbert::QbertMoveCommand qbertMoveRightCommand{ coilyObject.get(),  glm::vec2{1,0} };
		qbert::QbertMoveCommand qbertMoveLeftCommand{ coilyObject.get(),  glm::vec2{-1,0} };
		qbert::QbertMoveCommand qbertMoveTopCommand{ coilyObject.get(),  glm::vec2{0,1} };
		qbert::QbertMoveCommand qbertMoveDownCommand{ coilyObject.get(),  glm::vec2{0,-1} };

		gamepadController->Bind(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveRightCommand), dae::InputType::DOWN);
		gamepadController->Bind(XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<qbert::QbertMoveCommand>(qbertMoveLeftCommand), dae::InputType::DOWN);
		gamepadController->Bind(XINPUT_GAMEPAD_DPAD_UP, std::make_unique<qbert::QbertMoveCommand>(qbertMoveTopCommand), dae::InputType::DOWN);
		gamepadController->Bind(XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<qbert::QbertMoveCommand>(qbertMoveDownCommand), dae::InputType::DOWN);

		dae::InputManager::GetInstance().AddController(std::move(gamepadController));
		
	}
	else
	{
		coilyObject->AddComponent<qbert::FollowPlayerComponent>(pPlayerObjects, pMapComponent);
	}

	return coilyObject;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateUgg(bool)
{
	std::unique_ptr<dae::GameObject> uggObject = std::make_unique<dae::GameObject>();


	return uggObject;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateSlick(const bool isSlick, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent)
{
	std::unique_ptr<dae::GameObject> slickObject = std::make_unique<dae::GameObject>();
	slickObject->AddComponent<dae::FSMManagerComponent<SlickState, SlickPreparingState>>();

	const int spriteRow{ static_cast<int>(isSlick) };
	slickObject->AddComponent<dae::ImageComponent>("qbert/Slick_Sam_Spritesheet.png", true, 0.0f, 0.0f, 2, 2, spriteRow, 0);
	slickObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	
	slickObject->AddComponent<qbert::FallComponent>();
	slickObject->AddComponent<qbert::SlickDirection>(pMapComponent);
	slickObject->AddComponent<qbert::TileDeactivatorComponent>(pMapComponent);
	slickObject->AddComponent<qbert::PlayerKillableComponent>(pPlayerObjects);
	slickObject->AddComponent<qbert::DeadFallComponent>();
	slickObject->AddComponent<qbert::SlickAnimatorComponent>();

	return slickObject;
}
