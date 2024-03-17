#pragma once
#include <vector>
#include <SDL.h>
#include <memory>

#include <windows.h>
#include <Xinput.h>
#include <SDL_syswm.h>

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
		virtual void Bind(GameObject* pActor) = 0;


	protected:

		template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
		void AddToBind(const unsigned int newInput, T& newCommand)
		{
			m_Bindings.push_back({ newInput, std::make_unique<T>(newCommand) });
		}

		std::vector<Binding> m_Bindings;

	private:
		
	};

	class GamepadController final : public Controller
	{
	public:
		GamepadController();
		virtual ~GamepadController() override;

		virtual void ProcessInput() override;
		virtual void Bind(GameObject* pActor) override;
	private:


		class GamepadControllerImpl;
		GamepadControllerImpl* m_pImpl;


		/*bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;

		XINPUT_STATE m_PreviousState;
		XINPUT_STATE m_CurrentState;
		unsigned int m_ButtonsPressedThisFrame;
		unsigned int m_ButtonsReleasedThisFrame;
		int m_Index = 0;

		static int m_GlobalIndex;*/
	};
}


