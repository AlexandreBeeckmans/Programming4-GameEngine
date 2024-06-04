#include "QbertFSMManagerComponent.h"
#include "GameObject.h"
#include"PlayerState.h"


qbert::QbertFSMManagerComponent::QbertFSMManagerComponent(dae::GameObject* owner):
BaseComponent(owner)
{
	m_PlayerState = std::make_unique<WaitingState>(WaitingState{});
}
void qbert::QbertFSMManagerComponent::Init()
{
	m_PlayerState->Enter(*GetOwner());
}
void qbert::QbertFSMManagerComponent::Update()
{
	std::unique_ptr<PlayerState> pNewState = m_PlayerState->HandleTransitions();
	if(pNewState)
	{
		m_PlayerState->Exit();
		//delete m_PlayerState;
		m_PlayerState = std::move(pNewState);
		m_PlayerState->Enter(*GetOwner());
	}

	m_PlayerState->Update();
}

