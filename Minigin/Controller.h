#pragma once
#include <vector>
#include <SDL.h>
#include <memory>

#include "Command.h"


namespace dae
{
	class GameObject;

	enum class InputType
	{
		DOWN,
		UP,
		TRIGGERED,
		THUMBSTICK
	};


	struct Binding
	{
		unsigned int input{};
		std::unique_ptr<Command> command{};
		InputType inputType{};
	};

	class Controller
	{
	public:

		virtual ~Controller() = default;

		virtual void ProcessInput() = 0;

		virtual void Bind(const unsigned int input, std::unique_ptr<Command> pCommand, InputType inputType) = 0;


	protected:

		//template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
		void AddToBind(const unsigned int newInput, std::unique_ptr<Command> pNewCommand, InputType inputType)
		{
			m_Bindings.push_back({ newInput, std::move(pNewCommand), inputType });
		}

		std::vector<Binding> m_Bindings;
		
	};

	class GamepadController final : public Controller
	{
	public:
		GamepadController();
		virtual ~GamepadController() override;

		virtual void ProcessInput() override;
		virtual void Bind(const unsigned int input, std::unique_ptr<Command> pCommand, InputType inputType) override;
	private:
		class GamepadControllerImpl;
		GamepadControllerImpl* m_pImpl;
	};
}


