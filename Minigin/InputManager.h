#pragma once

#include <memory>
#include <windows.h>
#include <Xinput.h>
#include <SDL_syswm.h>

#include <vector>

#include "Command.h"
#include "Singleton.h"



namespace dae
{
	class GameObject;

	struct InputBinding
	{
		SDL_Keycode input;
		std::unique_ptr<Command> command;
	};

	struct GamepadBinding
	{
		unsigned int button;
		std::unique_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void SetMoveKeyboardCommandActor(GameObject* pActor);
		void SetMoveGamepadCommandActor(GameObject* pActor);


	private:

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;

		/*std::unique_ptr <Move> m_pWKey;
		std::unique_ptr <Move> m_pAKey;
		std::unique_ptr <Move> m_pSKey;
		std::unique_ptr <Move> m_pDKey;*/

		std::unique_ptr<Move> m_pDUp;
		std::unique_ptr<Move> m_pDLeft;
		std::unique_ptr<Move> m_pDDown;
		std::unique_ptr<Move> m_pDRight;

		XINPUT_STATE m_PreviousState;
		XINPUT_STATE m_CurrentState;
		unsigned int m_ButtonsPressedThisFrame;
		unsigned int m_ButtonsReleasedThisFrame;

		std::vector<InputBinding> m_KeyboardBindings;
		std::vector<GamepadBinding> m_GamepadBindings;
	};
}
