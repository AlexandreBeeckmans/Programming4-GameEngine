#pragma once

#include <memory>
#include <vector>

#include "Command.h"
#include "Singleton.h"
#include "Controller.h"



namespace dae
{
	class GameObject;

	struct InputBinding
	{
		SDL_Scancode input;
		std::unique_ptr<Command> command;
		InputType inputType{};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		//Helper function to make move bindning easier
		void SetMoveKeyboardCommandActor(GameObject* pActor);


		//Add a controller of any type deriving from a base controller
		void AddController(std::unique_ptr<Controller> controller);

		void BindKeyboardInput(SDL_Scancode input, std::unique_ptr<Command> command, InputType inputType);

		void UnbindAll();

	private:
		std::vector<InputBinding> m_KeyboardBindings;
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
