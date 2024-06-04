#include "CoilyFSMManagerComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

#include "MapComponent.h"
#include "CoilyState.h"
qbert::CoilyFSMManagerComponent::CoilyFSMManagerComponent(dae::GameObject* owner) :
BaseComponent(owner)
{
	

	m_State = std::make_unique<CoilyPreparingState>();
	m_State->Enter(*GetOwner());
}

void qbert::CoilyFSMManagerComponent::Update()
{
	std::unique_ptr<CoilyState> pNewState = m_State->HandleTransitions();
	if (pNewState)
	{
		m_State->Exit();
		m_State = std::move(pNewState);
		m_State->Enter(*GetOwner());
	}

	m_State->Update();

}


