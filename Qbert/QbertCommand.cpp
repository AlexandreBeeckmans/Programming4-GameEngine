#include "QbertCommand.h"

#include "GameObject.h"
#include "InputDirectionComponent.h"
#include "QbertScenes.h"

qbert::QbertMoveCommand::QbertMoveCommand(dae::GameObject* pObject, const glm::vec2& direction) :
	GameObjectCommand{ pObject },
	m_Direction(direction)
{

}

void qbert::QbertMoveCommand::Execute()
{
	GetGameActor()->GetComponent<InputDirectionComponent>()->SetInputDirection(m_Direction);
}

void qbert::GoNextSceneCommand::Execute()
{
	QbertScenes::goNext = true;
}
