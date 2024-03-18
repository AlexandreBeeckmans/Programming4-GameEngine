#include <SDL.h>
#include "InputManager.h"

#include <backends/imgui_impl_sdl2.h>

#include "GameObject.h"
#include <glm/vec2.hpp>



bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (auto& binding : m_KeyboardBindings)
			{
				if (e.key.keysym.sym == binding.input)
					binding.command->Execute();
			}

		}
		if (e.type == SDL_KEYUP) 
		{
			for (auto& binding : m_KeyboardBindings)
			{
				if (e.key.keysym.sym == binding.input)
					binding.command->Undo();
			}
		}
		
		//ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	//Gamepads
	for (auto& controller : m_Controllers)
	{
		controller->ProcessInput();
	}

	return true;
}

void dae::InputManager::AddController(std::unique_ptr<Controller> controller)
{
	m_Controllers.push_back(std::move(controller));

}

void dae::InputManager::BindKeyboardInput(const SDL_Keycode& input, std::unique_ptr<Command> command)
{
	m_KeyboardBindings.push_back({ input, std::move(command) });
}
void dae::InputManager::SetMoveKeyboardCommandActor(dae::GameObject* pActor)
{ 
	std::unique_ptr<Move> wKey{ std::make_unique<Move>(pActor, glm::vec2{ 0.0f, -1.0f }) };
	std::unique_ptr<Move> aKey{ std::make_unique<Move>(pActor, glm::vec2{ -1.0f, 0.0f }) };
	std::unique_ptr<Move> sKey{ std::make_unique<Move>(pActor, glm::vec2{ 0.0f, 1.0f }) };
	std::unique_ptr<Move> dKey{ std::make_unique<Move>(pActor, glm::vec2{ 1.0f, 0.0f }) };


	BindKeyboardInput(SDLK_w, std::move(wKey));
	BindKeyboardInput(SDLK_a, std::move(aKey));
	BindKeyboardInput(SDLK_s, std::move(sKey));
	BindKeyboardInput(SDLK_d, std::move(dKey));
}
