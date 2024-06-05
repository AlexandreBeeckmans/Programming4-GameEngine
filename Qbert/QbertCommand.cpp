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

qbert::SelectCommand::SelectCommand(dae::GameObject* pObject, int direction, const float discplacement):
GameObjectCommand(pObject),
m_Direction(direction/std::abs(direction)),
m_Discplacement(discplacement)
{
	
}

void qbert::SelectCommand::Execute()
{
	if(SceneStates::IncrementGameMode(m_Direction))
		GetGameActor()->Translate(glm::vec2{ 0, m_Discplacement * static_cast<float>(m_Direction) });
}

