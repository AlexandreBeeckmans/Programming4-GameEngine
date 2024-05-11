#include <SDL.h>
#include "InputManager.h"

#include <backends/imgui_impl_sdl2.h>

#include "GameObject.h"
#include <glm/vec2.hpp>



bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

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
				if (pStates[binding.input] && binding.inputType == InputType::DOWN)
					binding.command->Execute();
			}

		}
		if (e.type == SDL_KEYUP) 
		{
			for (auto& binding : m_KeyboardBindings)
			{
				if (pStates[binding.input] && binding.inputType == InputType::UP)
					binding.command->Execute();
			}
		}
		
		//ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);

	}
	for (const InputBinding& action : m_KeyboardBindings)
	{
		if (pStates[action.input] && action.inputType == dae::InputType::TRIGGERED)
		{
			action.command->Execute();
		}
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

void dae::InputManager::BindKeyboardInput(SDL_Scancode input, std::unique_ptr<Command> command, InputType inputType)
{
	m_KeyboardBindings.push_back({ input, std::move(command), inputType });
}

void dae::InputManager::UnbindAll()
{
	m_KeyboardBindings.clear();
	m_Controllers.clear();
}
