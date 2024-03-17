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
	void DoBindMove(GameObject* pActor);




	//template <typename T, typename = std::enable_if<std::is_base_of<Command, T>::value>::type>
	void DoBind(const unsigned int input, std::unique_ptr<Command> pCommand)
	{
		m_pOwner->AddToBind(input, std::move(pCommand));
	}
private:
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;

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

void dae::GamepadController::Bind(const unsigned int input, std::unique_ptr<Command> pCommand)
{
	m_pImpl->DoBind(input, std::move(pCommand));
}

void dae::GamepadController::GamepadControllerImpl::DoBindMove(GameObject* pActor)
{
	Move up{ pActor, glm::vec2{ 0.0f, -1.0f } };
	Move left{ pActor, glm::vec2{ -1.0f, 0.0f } };
	Move down{ pActor, glm::vec2{ 0.0f, 1.0f } };
	Move right{ pActor, glm::vec2{ 1.0f, 0.0f } };


	DoBind(XINPUT_GAMEPAD_DPAD_UP, std::make_unique<Move>(up));
	DoBind(XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<Move>(left));
	DoBind(XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<Move>(down));
	DoBind(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<Move>(right));
}
void dae::GamepadController::BindMoveInput(GameObject* pActor)
{
	m_pImpl->DoBindMove(pActor);
}

bool dae::GamepadController::GamepadControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}
bool dae::GamepadController::GamepadControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}



