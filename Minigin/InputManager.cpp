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
			//Test Purpose
			if (e.key.keysym.sym == SDLK_z)
			{
				m_pMoveP1Command->Execute();
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			
		}
		// etc...

		
		//ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}


void dae::InputManager::SetMoveUpCommandActor(dae::GameObject* pActor)
{ 
	m_pMoveP1Command = std::make_unique<dae::Move>(pActor, glm::vec2{100.0f,100.0f});
}
