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
		void SetMoveKeyboardCommandActor(GameObject* pActor);


		//Add a controller of any type deriving from a base controller
		template <typename T, typename = std::enable_if<std::is_base_of<Controller, T>::value>::type>
		void AddController(GameObject* pActor)
		{
			std::unique_ptr <T> controllerToAdd{std::make_unique<T>()};
			controllerToAdd->Bind(pActor);

			m_Controllers.push_back(std::move(controllerToAdd));

		}

	private:
		std::vector<InputBinding> m_KeyboardBindings;
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
