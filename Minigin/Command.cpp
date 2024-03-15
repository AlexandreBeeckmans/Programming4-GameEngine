#include "Command.h"
#include "GameObject.h"
#include "Time.h"

#include "MoveComponent.h"

dae::GameObjectCommand::GameObjectCommand(dae::GameObject* pActor) :
	m_pActor{pActor}
{}


dae::Move::Move(dae::GameObject* pActor, const glm::vec2& direction, const bool isXAxis) :
	GameObjectCommand::GameObjectCommand{ pActor },
	m_Direction{ glm::normalize(direction) },
	m_IsXAxis{ isXAxis }
{}

void dae::Move::Execute()
{

	GetGameActor()->GetComponent<dae::MoveComponent>()->SetMovement(m_Direction, m_IsXAxis);
}

void dae::Move::Undo()
{
	GetGameActor()->GetComponent<dae::MoveComponent>()->SetMovement({ 0,0 }, m_IsXAxis);
}

