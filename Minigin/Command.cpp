#include "Command.h"
#include "GameObject.h"
#include "Time.h"

#include "MoveComponent.h"
#include "HealthComponent.h"

#include "Observer.h"

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


dae::Die::Die(dae::GameObject* pActor):
	GameObjectCommand::GameObjectCommand{ pActor }
{

}

void dae::Die::Execute()
{
	GetGameActor()->GetComponent<dae::HealthComponent>()->RemoveLive();
	GetGameActor()->GetDieEvent()->NotifyObservers({ EventType::PLAYER_DIED }, GetGameActor());
}
void dae::Die::Undo(){}

