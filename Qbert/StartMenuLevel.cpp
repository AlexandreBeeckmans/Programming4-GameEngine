#include "StartMenuLevel.h"

#include "BlinkingComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "Minigin.h"
#include "QbertCommand.h"
#include "ResourceManager.h"

qbert::StartMenuLevel::StartMenuLevel()
	//Level("Start Menu Level")
{

}

void qbert::StartMenuLevel::Load()
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
		static_cast<int>(static_cast<float>(titleObject->GetComponent<dae::ImageComponent>()->GetShape().y + titleObject->GetComponent<dae::ImageComponent>()->GetShape().h) + titleOffset + 1 * titleDiscplacement)
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
