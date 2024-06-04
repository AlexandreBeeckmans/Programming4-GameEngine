#include "SlickFSMManagerComponent.h"

qbert::SlickFSMManagerComponent::SlickFSMManagerComponent(dae::GameObject* owner):
	BaseComponent(owner)
{
	m_State = std::make_unique<SlickPreparingState>();
}


void qbert::SlickFSMManagerComponent::Init()
{
	m_State->Enter(*GetOwner());
}

void qbert::SlickFSMManagerComponent::Update()
{
	std::unique_ptr<SlickState> pNewState = m_State->HandleTransitions();
	if (pNewState)
	{
		m_State->Exit();
		m_State = std::move(pNewState);
		m_State->Enter(*GetOwner());
	}

	m_State->Update();

}
