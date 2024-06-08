#include "WritableNameComponent.h"

#include "GameObject.h"
#include "QbertGameState.h"
#include "QbertScenes.h"
#include "TextComponent.h"

qbert::WritableNameComponent::WritableNameComponent(dae::GameObject* pOwner) :
BaseComponent(pOwner)
{
}

void qbert::WritableNameComponent::Init()
{
	m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void qbert::WritableNameComponent::IncrementCurrentLetter(const int direction)
{
	m_pTextComponent->IncrementLetter(m_CurrentWriteIndex, direction);
	QbertGameState::GetInstance().SetName(m_pTextComponent->GetText());
}

void qbert::WritableNameComponent::IncrementLetterIndex(const int direction, const std::vector<dae::GameObject*>& pArrow)
{
	if(static_cast<size_t>(m_CurrentWriteIndex + direction) < m_pTextComponent->GetText().size()
		&&
		m_CurrentWriteIndex + direction > -1)
	{
		m_CurrentWriteIndex += direction;

		for(auto arrow : pArrow)
		{
			const glm::vec2 arrowTranslate
			{
				direction * static_cast<int>(static_cast<float>(arrow->GetComponent<dae::ImageComponent>()->GetShape().w) / dae::ImageComponent::GetSpriteScale()),
				0
			};
			arrow->Translate(arrowTranslate);
		}
		
	}
}
