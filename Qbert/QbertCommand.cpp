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
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	QbertScenes::GetInstance().goNext = true;
}

void qbert::SkipLevelCommand::Execute()
{
	QbertScenes::GetInstance().skipLevel = true;
	QbertScenes::GetInstance().goNext = true;
}

qbert::IncrementLetterCommand::IncrementLetterCommand(dae::GameObject* pObject, const int direction) :
GameObjectCommand(pObject),
m_Direction(direction)
{
}

void qbert::IncrementLetterCommand::Execute()
{
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	GetGameActor()->GetComponent<qbert::WritableNameComponent>()->IncrementCurrentLetter(m_Direction);
}

qbert::IncrementLetterIndexCommand::IncrementLetterIndexCommand(const int direction, dae::GameObject* pObject, const std::vector<dae::GameObject*>& pArrow):
GameObjectCommand(pObject),
m_pArrow(pArrow),
m_Direction(direction)
{
}

void qbert::IncrementLetterIndexCommand::Execute()
{
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	GetGameActor()->GetComponent<qbert::WritableNameComponent>()->IncrementLetterIndex(m_Direction, m_pArrow);
}

qbert::SelectCommand::SelectCommand(dae::GameObject* pObject, int direction, const float discplacement):
GameObjectCommand(pObject),
m_Direction(direction/std::abs(direction)),
m_Discplacement(discplacement)
{
	
}

void qbert::SelectCommand::Execute()
{
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::MENUSELECTION), 100.0f);
	if(SceneState::IncrementGameMode(m_Direction))
		GetGameActor()->Translate(glm::vec2{ 0, m_Discplacement * static_cast<float>(m_Direction) });
}

