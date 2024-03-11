#include "Command.h"
#include "GameObject.h"
#include "Time.h"

dae::GameObjectCommand::GameObjectCommand(dae::GameObject* pActor) :
	m_pActor{pActor}
{}



void dae::Move::Execute()
{
	glm::vec3 currentPos{ GetGameActor()->GetLocalPosition()};
	currentPos.x += Time::GetInstance().GetDeltaTime() * m_Speed.x;
	currentPos.y += Time::GetInstance().GetDeltaTime() * m_Speed.y;

	GetGameActor()->SetLocalPosition(currentPos);
}

dae::Move::Move(dae::GameObject* pActor, const glm::vec2& speed) :
	GameObjectCommand::GameObjectCommand{ pActor },
	m_Speed{speed}
{}

