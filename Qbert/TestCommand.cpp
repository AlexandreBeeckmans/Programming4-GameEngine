#include "TestCommand.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "MoveComponent.h"

dae::Die::Die(dae::GameObject* pActor) :
	GameObjectCommand{ pActor }
{}

void dae::Die::Execute()
{
	GetGameActor()->GetComponent<HealthComponent>()->RemoveLive();
}

dae::Score::Score(GameObject* pActor) :
	GameObjectCommand{ pActor }
{}

void dae::Score::Execute()
{
	constexpr int valueToIncrement{ 15 };
	GetGameActor()->GetComponent<ScoreComponent>()->IncrementScore(valueToIncrement);
}

dae::Move::Move(GameObject* pActor, const glm::vec2& direction) :
	GameObjectCommand{ pActor },
	m_Direction{ normalize(direction) }
{}

void dae::Move::Execute()
{
	const float speed = GetGameActor()->GetComponent<MoveComponent>()->GetSpeed();
	GetGameActor()->Translate(m_Direction * speed);
}
