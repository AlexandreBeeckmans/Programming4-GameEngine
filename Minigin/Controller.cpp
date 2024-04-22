#include "Controller.h"
#include <glm/vec2.hpp>

#include <windows.h>
#include <Xinput.h>
#include <SDL_syswm.h>
#include <iostream>


class dae::GamepadController::GamepadControllerImpl
{
public:
	GamepadControllerImpl(GamepadController* pOwner);

	void DoProcessInput();




	//template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
	void DoBind(const unsigned int input, std::unique_ptr<Command> pCommand, InputType inputType)
	{
		m_pOwner->AddToBind(input, std::move(pCommand), inputType);
	}
private:
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsDown(unsigned int button) const;

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	int m_Index = 0;

	static int m_GlobalIndex;

	GamepadController* m_pOwner{ nullptr };

};


dae::GamepadController::GamepadController()
{
	m_pImpl = new GamepadControllerImpl{this};
}
dae::GamepadController::~GamepadController()
{
	delete m_pImpl;
}

dae::GamepadController::GamepadControllerImpl::GamepadControllerImpl(GamepadController* pOwner)
{
	m_pOwner = pOwner;

	//Set the index
	m_Index = m_GlobalIndex;
	++m_GlobalIndex;
}

int dae::GamepadController::GamepadControllerImpl::m_GlobalIndex = 0;



void dae::GamepadController::GamepadControllerImpl::DoProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_Index, &m_CurrentState);

	

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	if (m_ButtonsPressedThisFrame != 0) std::cout << "button\n";

	//Pressed
	for (auto& binding : m_pOwner->m_Bindings)
	{
		if (IsDownThisFrame(binding.input) && binding.inputType == InputType::DOWN)
			binding.command->Execute();

		if (IsDown(binding.input) && binding.inputType == InputType::TRIGGERED)
			binding.command->Execute();
	}
}
void dae::GamepadController::ProcessInput()
{
	m_pImpl->DoProcessInput();
}

void dae::GamepadController::Bind(const unsigned int input, std::unique_ptr<Command> pCommand, InputType inputType)
{
	m_pImpl->DoBind(input, std::move(pCommand), inputType);
}

bool dae::GamepadController::GamepadControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::GamepadController::GamepadControllerImpl::IsDown(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
bool dae::GamepadController::GamepadControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}



