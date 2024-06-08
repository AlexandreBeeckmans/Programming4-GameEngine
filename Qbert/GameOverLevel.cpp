#include "GameOverLevel.h"

#include "InputManager.h"
#include "Minigin.h"
#include "QbertCommand.h"
#include "QbertGameState.h"
#include "ResourceManager.h"
#include "WritableNameComponent.h"

qbert::GameOverLevel::GameOverLevel() = default;

void qbert::GameOverLevel::Load()
{
	const int currentScore{ QbertGameState::GetInstance().GetScoreSum() };
	ScoreData highScore{ QbertGameState::GetInstance().GetHighScore() };


	auto gameOverFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 55);
	dae::Font actualGameOverFont{ *gameOverFont };

	auto gameOverTextObject{ std::make_unique<dae::GameObject>() };
	gameOverTextObject->AddComponent<dae::TextComponent>("GAME OVER!", actualGameOverFont);
	const glm::vec2 gameOverPos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(gameOverTextObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 8.0f)
	};
	gameOverTextObject->SetLocalPosition(gameOverPos);


	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("qbert/Minecraft.ttf", 36);
	dae::Font actualScoreFont{ *scoreFont };

	auto nameObject{ std::make_unique<dae::GameObject>() };
	nameObject->AddComponent<dae::TextComponent>("AAA", actualGameOverFont);
	nameObject->AddComponent<qbert::WritableNameComponent>();




	const glm::vec2 namePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(nameObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f - 100)
	};
	nameObject->SetLocalPosition(namePos);


	auto selectionArrowObject{ std::make_unique<dae::GameObject>() };
	selectionArrowObject->AddComponent<dae::ImageComponent>("qbert/Selection_Arrow_Up.png");
	selectionArrowObject->GetComponent<dae::ImageComponent>()->SetWidth(nameObject->GetComponent<dae::ImageComponent>()->GetShape().w / 3, true);
	const glm::vec2 selectArrowPos
	{
		namePos.x,
		namePos.y - static_cast<float>(selectionArrowObject->GetComponent<dae::ImageComponent>()->GetShape().h)
	};
	selectionArrowObject->SetLocalPosition(selectArrowPos);

	auto selectionArrowDownObject{ std::make_unique<dae::GameObject>() };
	selectionArrowDownObject->AddComponent<dae::ImageComponent>("qbert/Selection_Arrow_Down.png");
	selectionArrowDownObject->GetComponent<dae::ImageComponent>()->SetWidth(nameObject->GetComponent<dae::ImageComponent>()->GetShape().w / 3, true);
	const glm::vec2 selectArrowDownPos
	{
		namePos.x,
		namePos.y + nameObject->GetComponent<dae::TextComponent>()->GetShape().h
	};
	selectionArrowDownObject->SetLocalPosition(selectArrowDownPos);

	auto yourScoreTextObject{ std::make_unique<dae::GameObject>() };
	yourScoreTextObject->AddComponent<dae::TextComponent>("YOUR SCORE:", actualGameOverFont);
	const glm::vec2 yourScorePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(yourScoreTextObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f)
	};
	yourScoreTextObject->SetLocalPosition(yourScorePos);

	auto currentScoreObject{ std::make_unique<dae::GameObject>() };
	currentScoreObject->AddComponent<dae::TextComponent>(std::to_string(currentScore), actualGameOverFont);
	const glm::vec2 currentScorePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(currentScoreObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f + 50)
	};
	currentScoreObject->SetLocalPosition(currentScorePos);

	auto highScoreTextObject{ std::make_unique<dae::GameObject>() };
	highScoreTextObject->AddComponent<dae::TextComponent>("HIGH SCORE:", actualGameOverFont);
	const glm::vec2 highScoreTextPos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(highScoreTextObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f + 100)
	};
	highScoreTextObject->SetLocalPosition(highScoreTextPos);

	auto highScoreObject{ std::make_unique<dae::GameObject>() };
	highScoreObject->AddComponent<dae::TextComponent>(highScore.name + ": " + std::to_string(highScore.score), actualGameOverFont);
	const glm::vec2 highScorePos
	{
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(highScoreObject->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f),
		static_cast<int>(static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f + 150)
	};
	highScoreObject->SetLocalPosition(highScorePos);


	qbert::IncrementLetterCommand incrementLetterCommand{ nameObject.get(), 1 };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_UP, std::make_unique<qbert::IncrementLetterCommand>(incrementLetterCommand), dae::InputType::DOWN);

	qbert::IncrementLetterCommand decrementLetterCommand{ nameObject.get(), -1 };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_DOWN, std::make_unique<qbert::IncrementLetterCommand>(decrementLetterCommand), dae::InputType::DOWN);

	qbert::IncrementLetterIndexCommand incrementLetterIndexCommand{ 1, nameObject.get(), {selectionArrowObject.get(), selectionArrowDownObject.get()} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_RIGHT, std::make_unique<qbert::IncrementLetterIndexCommand>(incrementLetterIndexCommand), dae::InputType::DOWN);

	qbert::IncrementLetterIndexCommand decrementLetterIndexCommand{ -1, nameObject.get(), {selectionArrowObject.get(), selectionArrowDownObject.get()} };
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_LEFT, std::make_unique<qbert::IncrementLetterIndexCommand>(decrementLetterIndexCommand), dae::InputType::DOWN);


	auto& scene = dae::SceneManager::GetInstance().CreateScene("GameOverMenu");
	scene.Add(std::move(gameOverTextObject));
	scene.Add(std::move(nameObject));
	scene.Add(std::move(yourScoreTextObject));
	scene.Add(std::move(currentScoreObject));
	scene.Add(std::move(highScoreTextObject));
	scene.Add(std::move(highScoreObject));
	scene.Add(std::move(selectionArrowObject));
	scene.Add(std::move(selectionArrowDownObject));

	QbertGameState::GetInstance().SetScore(currentScore);

	qbert::GoNextSceneCommand goNextCommand{};
	dae::InputManager::GetInstance().BindKeyboardInput(SDL_SCANCODE_SPACE, std::make_unique<qbert::GoNextSceneCommand>(goNextCommand), dae::InputType::DOWN);
}
