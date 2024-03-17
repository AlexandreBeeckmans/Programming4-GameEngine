#include "Command.h"
#include "GameObject.h"
#include "Time.h"

#include "MoveComponent.h"

dae::GameObjectCommand::GameObjectCommand(dae::GameObject* pActor) :
	m_pActor{pActor}
{}


dae::Move::Move(dae::GameObject* pActor, const glm::vec2& direction) :
	GameObjectCommand::GameObjectCommand{ pActor },
	m_Direction{ glm::normalize(direction) }
{}

void dae::Move::Execute()
{
	if (m_IsMoving) return;

	GetGameActor()->GetComponent<dae::MoveComponent>()->SetMovement(m_Direction);
	m_IsMoving = true;
}

void dae::Move::Undo()
{

	GetGameActor()->GetComponent<dae::MoveComponent>()->SetMovement(-m_Direction);
	m_IsMoving = false;
}

