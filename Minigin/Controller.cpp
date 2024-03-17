#include "Controller.h"
#include <glm/vec2.hpp>

#include <windows.h>
#include <Xinput.h>
#include <SDL_syswm.h>


class dae::GamepadController::GamepadControllerImpl
{
public:
	GamepadControllerImpl(GamepadController* pOwner);

	void DoProcessInput();
	void DoBind(GameObject* pActor);
private:
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;

	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;
	unsigned int m_ButtonsPressedThisFrame;
	unsigned int m_ButtonsReleasedThisFrame;
	int m_Index = 0;

	static int m_GlobalIndex;

	GamepadController* m_pOwner;

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

	//Pressed
	for (auto& binding : m_pOwner->m_Bindings)
	{
		if (IsDownThisFrame(binding.input))
			binding.command->Execute();
	}

	//Released
	for (auto& binding : m_pOwner->m_Bindings)
	{
		if (IsUpThisFrame(binding.input))
			binding.command->Undo();
	}
}
void dae::GamepadController::ProcessInput()
{
	m_pImpl->DoProcessInput();
}

void dae::GamepadController::GamepadControllerImpl::DoBind(GameObject* pActor)
{
	Move up{ pActor, glm::vec2{ 0.0f, -1.0f } };
	Move left{ pActor, glm::vec2{ -1.0f, 0.0f } };
	Move down{ pActor, glm::vec2{ 0.0f, 1.0f } };
	Move right{ pActor, glm::vec2{ 1.0f, 0.0f } };

	m_pOwner->AddToBind(XINPUT_GAMEPAD_DPAD_UP, up);
	m_pOwner->AddToBind(XINPUT_GAMEPAD_DPAD_LEFT, left);
	m_pOwner->AddToBind(XINPUT_GAMEPAD_DPAD_DOWN, down);
	m_pOwner->AddToBind(XINPUT_GAMEPAD_DPAD_RIGHT, right);

	//Set the index
	m_Index = m_GlobalIndex;
	++m_GlobalIndex;
}
void dae::GamepadController::Bind(GameObject* pActor)
{
	m_pImpl->DoBind(pActor);
}

bool dae::GamepadController::GamepadControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}
bool dae::GamepadController::GamepadControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}



