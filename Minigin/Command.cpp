#include "Command.h"

#include "ServiceLocator.h"

void dae::MuteCommand::Execute()
{
	ServiceLocator::GetInstance().Mute();
}

dae::GameObjectCommand::GameObjectCommand(GameObject* pActor) :
	m_pActor{pActor}
{}

