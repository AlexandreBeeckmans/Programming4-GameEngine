
#include <windows.h>
#include <Xinput.h>
#include <fstream>

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
#include "QbertGameState.h"
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
#include "UggAnimatorComponent.h"

#include "UggStates.h"
#include "UggDirectionComponent.h"

#include "WritableNameComponent.h"

void qbert::QbertScenes::Init()
{
	m_pSceneState->Enter();
}

void qbert::QbertScenes::LeaveGameOverScreen()
{
	QbertGameState::GetInstance().TestNewScore();
}

void qbert::QbertScenes::Update()
{
	std::unique_ptr<SceneState> pNewState = m_pSceneState->HandleTransitions();
	if (pNewState)
	{
		m_pSceneState->Exit();
		m_pSceneState = std::move(pNewState);
		m_pSceneState->Enter();
	}

	m_pSceneState->Update();
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

	playerObject->AddComponent<dae::ScoreComponent>(QbertGameState::GetInstance().GetScoreAtIndex(playerNb - 1));
	playerObject->GetComponent<dae::ScoreComponent>()->AddObserver(&QbertGameState::GetInstance());
	QbertGameState::GetInstance().AddScoreComponent(playerObject->GetComponent<dae::ScoreComponent>());


	playerObject->AddComponent<dae::HealthComponent>(QbertGameState::GetInstance().GetLiveAtIndex(playerNb - 1));
	playerObject->GetComponent<dae::HealthComponent>()->AddObserver(&QbertGameState::GetInstance());
	QbertGameState::GetInstance().AddHealthComponents(playerObject->GetComponent<dae::HealthComponent>());


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
	
	coilyObject->AddComponent<dae::FSMManagerComponent<CoilyState, CoilyPreparingState>>();
	coilyObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	coilyObject->AddComponent<qbert::FallComponent>();
	coilyObject->AddComponent<qbert::KillerComponent>(pPlayerObjects);
	coilyObject->AddComponent<qbert::CoilyAnimatorComponent>();
	coilyObject->AddComponent<qbert::DeadFallComponent>();

	coilyObject->GetComponent<qbert::GridMoveComponent>()->SetCurrentIndex(coilyNb * (pMapComponent->GetNbRows() - 1));

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
		coilyObject->AddComponent<dae::ImageComponent>("qbert/Coily_Versus_Spritesheet.png", true, 0.0f, 0.0f, 1, 10, 0, 0);
		
	}
	else
	{
		coilyObject->AddComponent<dae::ImageComponent>("qbert/Coily Spritesheet.png", true, 0.0f, 0.0f, 1, 10, 0, 0);
		coilyObject->AddComponent<qbert::FollowPlayerComponent>(pPlayerObjects, pMapComponent);
	}

	return coilyObject;
}

std::unique_ptr<dae::GameObject> qbert::QbertScenes::CreateUgg(bool isLeft, std::vector<std::unique_ptr<dae::GameObject>>* pPlayerObjects, MapComponent* pMapComponent)
{
	std::unique_ptr<dae::GameObject> uggObject = std::make_unique<dae::GameObject>();

	uggObject->AddComponent<dae::ImageComponent>("qbert/Ugg_Wrongway_Spritesheet.png", true, 0.0f, 0.0f, 2, 4, 0, 0);

	uggObject->AddComponent<dae::FSMManagerComponent<UggState, UggPreparingState>>();
	uggObject->AddComponent<qbert::GridMoveComponent>(pMapComponent);
	uggObject->AddComponent<qbert::FallComponent>();
	uggObject->AddComponent<qbert::KillerComponent>(pPlayerObjects);
	uggObject->AddComponent<qbert::UggDirectionComponent>(pMapComponent, isLeft);
	uggObject->AddComponent<qbert::DeadFallComponent>();
	uggObject->AddComponent<qbert::UggAnimatorComponent>(pMapComponent);


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

void qbert::QbertScenes::CreateGameUI(dae::Scene* pScene, const std::vector<std::unique_ptr<dae::GameObject>>& playerObjects, const int level, const int round)
{
	
	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 24);

	//Score
#pragma region SCORE1_OBJECT
	for(size_t i{0}; i < playerObjects.size(); ++i)
	{
		CreateScoreUIObject(pScene, playerObjects[i], static_cast<int>(i));
	}
#pragma endregion

	CreateNextTileUIObject(pScene, level, round);

#pragma region LEVEL_INDICATOR
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
	pScene->Add(std::move(levelUIObject));
#pragma endregion


	//Lives
#pragma region LIVE1_OBJECT
	auto livesUIObject = std::make_unique<dae::GameObject>();
	livesUIObject->AddComponent<dae::ImageComponent>("qbert/Lives_UI_P1.png");
	livesUIObject->SetLocalPosition(0, 150);
	livesUIObject->AddComponent<HealthUIComponent>(livesUIObject->GetComponent<dae::ImageComponent>());

	livesUIObject->GetComponent<qbert::HealthUIComponent>()->SetHealthComponent(playerObjects[0]->GetComponent<dae::HealthComponent>());
	playerObjects[0]->GetComponent<dae::HealthComponent>()->AddObserver(livesUIObject->GetComponent<qbert::HealthUIComponent>());
	pScene->Add(std::move(livesUIObject));
#pragma endregion

#pragma region LIVE2_OBJECT
	if (playerObjects.size() > 1)
	{
		auto lives2UIObject = std::make_unique<dae::GameObject>();
		lives2UIObject->AddComponent<dae::ImageComponent>("qbert/Lives_UI_P2.png");
		lives2UIObject->SetLocalPosition(0, 150);
		lives2UIObject->AddComponent<HealthUIComponent>(lives2UIObject->GetComponent<dae::ImageComponent>());

		lives2UIObject->GetComponent<qbert::HealthUIComponent>()->SetHealthComponent(playerObjects[1]->GetComponent<dae::HealthComponent>());
		playerObjects[1]->GetComponent<dae::HealthComponent>()->AddObserver(lives2UIObject->GetComponent<qbert::HealthUIComponent>());

		lives2UIObject->Translate(glm::vec2{ 50,0 });
		pScene->Add(std::move(lives2UIObject));
	}

#pragma endregion

	CreateControlsUIObject(pScene);
}

void qbert::QbertScenes::CreateScoreUIObject(dae::Scene* pScene, const std::unique_ptr<dae::GameObject>& pPlayerObject, const int playerNb)
{
	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 24);
	auto scoreUIObject = std::make_unique<dae::GameObject>();
	scoreUIObject->AddComponent<dae::TextComponent>("If it appears there is a problem", *scoreFont);


	dae::TextComponent* scoreTextComponent = scoreUIObject->GetComponent<dae::TextComponent>();
	scoreTextComponent->SetRelativePosition(25, 25);
	scoreTextComponent->SetColor({ 255,165,0, 255 });

	scoreUIObject->AddComponent<qbert::ScoreUIComponent>(scoreTextComponent, playerNb);
	scoreUIObject->GetComponent<qbert::ScoreUIComponent>()->SetScoreComponent(pPlayerObject->GetComponent<dae::ScoreComponent>());
	scoreUIObject->Translate(glm::vec2{ playerNb * 100,0 });

	pPlayerObject->GetComponent<dae::ScoreComponent>()->InitObserver(scoreUIObject->GetComponent<ScoreUIComponent>());
	pScene->Add(std::move(scoreUIObject));
}

void qbert::QbertScenes::CreateNextTileUIObject(dae::Scene* pScene, const int level, const int round)
{
	auto textFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 24);
	//NextTile
	auto changeToUIObject = std::make_unique<dae::GameObject>();
	changeToUIObject->SetLocalPosition(0, 45);

	//main text
	changeToUIObject->AddComponent<dae::TextComponent>("CHANGE TO:", *textFont);
	changeToUIObject->GetComponent<dae::TextComponent>()->SetColor({ 255,0,0,255 });


	std::vector<dae::ImageComponent*> pArrowComponents{};
	//2 arrows left
	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow.png", true, 15.0f, 20.0f);
	pArrowComponents.push_back({ changeToUIObject->GetComponent<dae::ImageComponent>(1) });

	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/ChangeTo_Arrow.png", true, 40.0f, 20.0f);
	pArrowComponents.push_back({ changeToUIObject->GetComponent<dae::ImageComponent>(2) });

	//middle tile
	changeToUIObject->AddComponent<dae::ImageComponent>("qbert/Color_Icons_Spritesheet.png", true, 55.0f, 20.0f, 2, 6, level % 2, round);

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
	pScene->Add(std::move(changeToUIObject));
}

void qbert::QbertScenes::CreateControlsUIObject(dae::Scene* pScene)
{
	auto controls1Object = std::make_unique<dae::GameObject>();
	controls1Object->AddComponent<dae::ImageComponent>("qbert/P1_Controls.png", true);
	controls1Object->GetComponent<dae::ImageComponent>()->Rescale(0.25f);
	const glm::vec2 pos1
	{
		0,
		dae::Minigin::GetWindowHeight() - controls1Object->GetComponent<dae::ImageComponent>()->GetShape().h
	};
	controls1Object->SetLocalPosition(pos1);
	pScene->Add(std::move(controls1Object));

	if (SceneState::GetGameMode() == GameMode::SOLO) return;
	auto controls2Object = std::make_unique<dae::GameObject>();
	std::string imagePath{ "qbert/P2_QBert_Controls.png" };
	if(SceneState::GetGameMode() == GameMode::VERSUS)
	{
		imagePath = "qbert/P2_Coily_Controls.png";
	}

	controls2Object->AddComponent<dae::ImageComponent>(imagePath, true);
	controls2Object->GetComponent<dae::ImageComponent>()->Rescale(0.25f);
	const glm::vec2 pos2
	{
		dae::Minigin::GetWindowWidth() - controls2Object->GetComponent<dae::ImageComponent>()->GetShape().w,
		dae::Minigin::GetWindowHeight() - controls2Object->GetComponent<dae::ImageComponent>()->GetShape().h
	};
	controls2Object->SetLocalPosition(pos2);
	pScene->Add(std::move(controls2Object));
}

void qbert::QbertScenes::CreateDiscObject(dae::Scene* pScene, MapComponent* pMapComponent, const bool isLeft, const int round)
{
	auto leftDiscObject = std::make_unique<dae::GameObject>();

	leftDiscObject->AddComponent<dae::ImageComponent>("qbert/Disk_Spritesheet.png", true, 0.0f, 0.0f, 1, 30, 0, 5 * round);
	leftDiscObject->AddComponent<dae::AnimatorComponent>(true, 0.25f, 4, 1, 5 * round, 0);
	leftDiscObject->AddComponent<qbert::DiscComponent>(pMapComponent, isLeft);

	pMapComponent->AddDisc(leftDiscObject->GetComponent<DiscComponent>());
	pScene->Add(std::move(leftDiscObject));
	
}


void qbert::QbertScenes::LoadSounds()
{
	std::string path{ dae::ResourceManager::GetInstance().GetPath() + "qbert/Sounds/" };
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Jump.wav", static_cast<int>(qbert::SoundType::JUMP));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Fall.wav", static_cast<int>(qbert::SoundType::FALL));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Round_Complete_Tune.wav", static_cast<int>(qbert::SoundType::WIN));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Level Screen Tune.wav", static_cast<int>(qbert::SoundType::LOAD));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Hit.wav", static_cast<int>(qbert::SoundType::HIT));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Change Selection.wav", static_cast<int>(qbert::SoundType::MENUSELECTION));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Coily Snake Jump.wav", static_cast<int>(qbert::SoundType::COILYJUMP));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Coily Fall.wav", static_cast<int>(qbert::SoundType::COILYFALL));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Disk Lift.wav", static_cast<int>(qbert::SoundType::DISKMOVE));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Disk Land.wav", static_cast<int>(qbert::SoundType::DISKLAND));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "SlickSam Caught.wav", static_cast<int>(qbert::SoundType::SLICKCAUGHT));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Swearing.wav", static_cast<int>(qbert::SoundType::SWEAR));
}
