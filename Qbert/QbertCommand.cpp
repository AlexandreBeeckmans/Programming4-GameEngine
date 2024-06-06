#include "QbertCommand.h"

#include "GameObject.h"
#include "InputDirectionComponent.h"
#include "QbertScenes.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"
#include "WritableNameComponent.h"

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
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	QbertScenes::GetInstance().goNext = true;
}

qbert::IncrementLetterCommand::IncrementLetterCommand(dae::GameObject* pObject) :
GameObjectCommand(pObject)
{
}

void qbert::IncrementLetterCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	GetGameActor()->GetComponent<qbert::WritableNameComponent>()->IncrementCurrentLetter();
}

qbert::IncrementLetterIndexCommand::IncrementLetterIndexCommand(dae::GameObject* pObject):
GameObjectCommand(pObject)
{
}

void qbert::IncrementLetterIndexCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	GetGameActor()->GetComponent<qbert::WritableNameComponent>()->IncrementLetterIndex();
}

qbert::SelectCommand::SelectCommand(dae::GameObject* pObject, int direction, const float discplacement):
GameObjectCommand(pObject),
m_Direction(direction/std::abs(direction)),
m_Discplacement(discplacement)
{
	
}

void qbert::SelectCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	if(SceneStates::IncrementGameMode(m_Direction))
		GetGameActor()->Translate(glm::vec2{ 0, m_Discplacement * static_cast<float>(m_Direction) });
}

