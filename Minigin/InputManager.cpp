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

void dae::InputManager::SetMoveKeyboardCommandActor(dae::GameObject* pActor)
{ 
	Move wKey{ pActor, glm::vec2{ 0.0f, -1.0f } };
	Move aKey{ pActor, glm::vec2{ -1.0f, 0.0f } };
	Move sKey{ pActor, glm::vec2{ 0.0f, 1.0f } };
	Move dKey{ pActor, glm::vec2{ 1.0f, 0.0f } };


	BindKeyboardInput(SDLK_w, wKey);
	BindKeyboardInput(SDLK_a, aKey);
	BindKeyboardInput(SDLK_s, sKey);
	BindKeyboardInput(SDLK_d, dKey);
}
