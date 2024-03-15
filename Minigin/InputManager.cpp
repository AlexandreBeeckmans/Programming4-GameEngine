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
		// etc...

		
		//ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}



	//Gamepad
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	//Pressed
	for (auto& binding : m_GamepadBindings)
	{
		if (IsDownThisFrame(binding.button))
			binding.command->Execute();
	}

	//Released
	for (auto& binding : m_GamepadBindings)
	{
		if (IsUpThisFrame(binding.button))
			binding.command->Undo();
	}


	return true;
}

void dae::InputManager::SetMoveKeyboardCommandActor(dae::GameObject* pActor)
{ 
	Move wKey{ pActor, glm::vec2{ 0.0f, -1.0f }, false };
	Move aKey{ pActor, glm::vec2{ -1.0f, 0.0f } };
	Move sKey{ pActor, glm::vec2{ 0.0f, 1.0f }, false };
	Move dKey{ pActor, glm::vec2{ 1.0f, 0.0f } };


	m_KeyboardBindings.push_back({ SDLK_w, std::make_unique<Move>(wKey) });
	m_KeyboardBindings.push_back({ SDLK_a, std::make_unique<Move>(aKey) });
	m_KeyboardBindings.push_back({ SDLK_s, std::make_unique<Move>(sKey) });
	m_KeyboardBindings.push_back({ SDLK_d, std::make_unique<Move>(dKey) });
}

void dae::InputManager::SetMoveGamepadCommandActor(GameObject* pActor)
{
	Move up(pActor, glm::vec2{ 0.0f, -1.0f }, false);
	Move left(pActor, glm::vec2{ -1.0f, 0.0f });
	Move down(pActor, glm::vec2{ 0.0f, 1.0f }, false);
	Move right(pActor, glm::vec2{ 1.0f, 0.0f });

	m_GamepadBindings.push_back({ XINPUT_GAMEPAD_DPAD_UP, std::make_unique<Move>(up) });
	m_GamepadBindings.push_back({ XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<Move>(left) });
	m_GamepadBindings.push_back({ XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<Move>(down) });
	m_GamepadBindings.push_back({ XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<Move>(right) });
}

bool dae::InputManager::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::InputManager::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}
