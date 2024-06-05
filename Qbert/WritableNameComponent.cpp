#include "WritableNameComponent.h"

#include "GameObject.h"
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

void qbert::WritableNameComponent::IncrementCurrentLetter()
{
	m_pTextComponent->IncrementLetter(m_CurrentWriteIndex);
	QbertScenes::GetInstance().SetName(m_pTextComponent->GetText());
}

void qbert::WritableNameComponent::IncrementLetterIndex()
{
	if(static_cast<size_t>(m_CurrentWriteIndex) < m_pTextComponent->GetText().size())
	{
		++m_CurrentWriteIndex;
	}
}
