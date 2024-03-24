#include "Observer.h"
#include "GameObject.h"

#include "TextComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include <string>

void dae::GameActionsObserver::Notify(Event event, dae::GameObject* pObject)
{
	switch (event.m_type) 
	{
		case EventType::PLAYER_DIED:
		{
			//Decrement Lives
			std::cout << "Player died : " << pObject << std::endl;

			const int livesRemaining{ pObject->GetComponent<HealthComponent>()->GetLivesRemaining() };

			std::string textString{ "Lives : " + std::to_string(livesRemaining) };

			TextComponent* pTextComponent{ static_cast<TextComponent*>(event.m_args[0]) };
			if (pTextComponent)
				pTextComponent->SetText(textString);
		}
		break;

		case EventType::PLAYER_SCORED:
		{
			std::cout << "Player scored : " << pObject << std::endl;

			const int currentScore{ pObject->GetComponent<ScoreComponent>()->GetScore() };

			std::string textString{ "Score : " + std::to_string(currentScore) };
			TextComponent* pTextComponent{ static_cast<TextComponent*>(event.m_args[0]) };
			if (pTextComponent)
				pTextComponent->SetText(textString);
		}
		break;

	}
}

