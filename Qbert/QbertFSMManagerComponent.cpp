#include "QbertFSMManagerComponent.h"

#include "GameObject.h"

#include"PlayerState.h"


qbert::QbertFSMManagerComponent::QbertFSMManagerComponent(dae::GameObject* owner):
BaseComponent(owner)
{
	m_PlayerState = new WaitingState{};
}
void qbert::QbertFSMManagerComponent::Init()
{
	m_PlayerState->Enter(*GetOwner());
}
void qbert::QbertFSMManagerComponent::Update()
{
	PlayerState* newState = m_PlayerState->HandleTransitions();
	if(newState)
	{
		m_PlayerState->Exit();
		delete m_PlayerState;
		m_PlayerState = newState;
		m_PlayerState->Enter(*GetOwner());
	}

	m_PlayerState->Update();
}

