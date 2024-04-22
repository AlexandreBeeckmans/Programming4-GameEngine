#include "QbertCommand.h"

#include "GameObject.h"
#include "QbertMoveComponent.h"

qbert::QbertMoveCommand::QbertMoveCommand(dae::GameObject* pObject, const glm::vec2& direction) :
	GameObjectCommand{ pObject },
	m_Direction(direction)
{

}

void qbert::QbertMoveCommand::Execute()
{
	GetGameActor()->GetComponent<QbertMoveComponent>()->SetDirection(m_Direction);
}
