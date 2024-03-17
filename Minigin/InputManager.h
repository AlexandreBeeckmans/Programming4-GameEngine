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
		template <typename T, typename = std::enable_if<std::is_base_of<Controller, T>::value>::type>
		void AddController(GameObject* pActor)
		{
			std::unique_ptr <T> controllerToAdd{std::make_unique<T>()};
			controllerToAdd->BindMoveInput(pActor);

			m_Controllers.push_back(std::move(controllerToAdd));

		}

		template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
		void BindKeyboardInput(const SDL_Keycode& input, const T& command)
		{
			m_KeyboardBindings.push_back({ input, std::make_unique<T>(command) });
		}

	private:
		std::vector<InputBinding> m_KeyboardBindings;
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
