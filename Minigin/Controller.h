#pragma once
#include <vector>
#include <SDL.h>
#include <memory>

#include "Command.h"


namespace dae
{
	class GameObject;


	struct Binding
	{
		unsigned int input{};
		std::unique_ptr<Command> command{};
	};

	class Controller
	{
	public:

		virtual ~Controller() = default;

		virtual void ProcessInput() = 0;

		virtual void Bind(const unsigned int input, std::unique_ptr<Command> pCommand) = 0;


	protected:

		//template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
		void AddToBind(const unsigned int newInput, std::unique_ptr<Command> pNewCommand)
		{
			m_Bindings.push_back({ newInput, std::move(pNewCommand) });
		}

		std::vector<Binding> m_Bindings;
		
	};

	class GamepadController final : public Controller
	{
	public:
		GamepadController();
		virtual ~GamepadController() override;

		virtual void ProcessInput() override;
		virtual void Bind(const unsigned int input, std::unique_ptr<Command> pCommand) override;

		virtual void BindMoveInput(GameObject* pActor);
	private:
		class GamepadControllerImpl;
		GamepadControllerImpl* m_pImpl;
	};
}


