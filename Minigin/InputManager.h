#pragma once

#include <memory>
#include <SDL_syswm.h>



#include <vector>

#include "Command.h"
#include "Singleton.h"
#include "Controller.h"



namespace dae
{
	class GameObject;

	struct InputBinding
	{
		SDL_Keycode input;
		std::unique_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		//Helper function to make move bindning easier
		void SetMoveKeyboardCommandActor(GameObject* pActor);


		//Add a controller of any type deriving from a base controller
		void AddController(std::unique_ptr<Controller> controller);

		void BindKeyboardInput(const SDL_Keycode& input, std::unique_ptr<Command> command);

	private:
		std::vector<InputBinding> m_KeyboardBindings;
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
