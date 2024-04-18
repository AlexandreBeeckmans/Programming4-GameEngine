#include "Command.h"
#include "GameObject.h"
#include "Time.h"

#include "MoveComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"


#include "Observer.h"
#include "QbertMoveComponent.h"

dae::GameObjectCommand::GameObjectCommand(dae::GameObject* pActor) :
	m_pActor{pActor}
{}


dae::Move::Move(dae::GameObject* pActor, const glm::vec2& direction) :
	GameObjectCommand::GameObjectCommand{ pActor },
	m_Direction{ glm::normalize(direction) }
{}

void dae::Move::Execute()
{
	const float speed = GetGameActor()->GetComponent<MoveComponent>()->GetSpeed();
	GetGameActor()->Translate(m_Direction * speed);
}


dae::Die::Die(dae::GameObject* pActor):
	GameObjectCommand::GameObjectCommand{ pActor }
	//m_pLivesText{pLivesText}
{}

void dae::Die::Execute()
{
	GetGameActor()->GetComponent<dae::HealthComponent>()->RemoveLive();
}

dae::Score::Score(GameObject* pActor) :
	GameObjectCommand::GameObjectCommand{ pActor }
	//m_pScoreText{pScoreText}
{}

void dae::Score::Execute()
{
	const int valueToIncrement{ 15 };
	GetGameActor()->GetComponent<ScoreComponent>()->IncrementScore(valueToIncrement);
}

qbert::QbertMoveCommand::QbertMoveCommand(dae::GameObject* pObject, const glm::vec2& direction) :
	GameObjectCommand{ pObject },
	m_Direction(direction)
{

}

void qbert::QbertMoveCommand::Execute()
{
	GetGameActor()->GetComponent<QbertMoveComponent>()->SetDirection(m_Direction);
}
