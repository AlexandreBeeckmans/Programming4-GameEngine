#include "Observer.h"
#include "GameObject.h"

#include "TextComponent.h"
#include "HealthComponent.h"
#include <string>


dae::GameActionsObserver::GameActionsObserver(TextComponent* pTextComponent):
	BaseObserver{},
	m_pRelatedTextComponent{pTextComponent}
{}

void dae::GameActionsObserver::Notify(Event event, dae::GameObject* pObject)
{
	switch (event.m_type) 
	{
	case EventType::PLAYER_DIED:
		//Decrement Lives
		std::cout << "Player died : " << pObject << std::endl;

		const int livesRemaining{ pObject->GetComponent<HealthComponent>()->GetLivesRemaining() };

		std::string textString{ "Lives : " + std::to_string(livesRemaining) };
		if (m_pRelatedTextComponent)
			m_pRelatedTextComponent->SetText(textString);

		break;
	}
}

