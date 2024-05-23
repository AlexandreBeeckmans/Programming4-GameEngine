#include "DiscComponent.h"
#include "GameObject.h"

#include <cstdlib>

#include "EngineTime.h"
#include "MapComponent.h"

qbert::DiscComponent::DiscComponent(dae::GameObject* pGameObject, MapComponent* pMap, const bool isLeft) :
BaseComponent(pGameObject),
m_pMap(pMap),
m_IsLeft(isLeft)
{
	SetRandomRow();
}

void qbert::DiscComponent::Update()
{
	if(m_IsActivated)
	{
		glm::vec2 direction = normalize(m_Target - glm::vec2{ GetWorldPosition().x, GetWorldPosition().y });
		constexpr float speed = 55.0f;

		GetOwner()->Translate(direction * speed * dae::EngineTime::GetInstance().GetDeltaTime());

		if (glm::length (m_Target - glm::vec2{ GetWorldPosition().x, GetWorldPosition().y }) < 1.0f)
		{
			//Has reached final position
			GetOwner()->SetVisible(false);
			GetOwner()->SetActive(false);
			GetOwner()->DetachAllChildren();
		}
	}
}

void qbert::DiscComponent::SetActive(const bool isActive, const QbertMoveComponent* qbert)
{
	m_IsActivated = isActive;
	if (qbert == nullptr) return;

	qbert->SetParent(GetOwner());
}

void qbert::DiscComponent::SetRandomRow()
{
	//select a random row
	m_Row = rand() % m_pMap->GetNbRows();

	//place the disc at the correct position
	glm::vec2 spawnPos
	{
		m_pMap->GetWorldPosition().x + static_cast<float>(m_pMap->GetTileWidth() * dae::ImageComponent::GetSpriteScale() * m_Row) / 2.0f - static_cast<float>(GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().w / 4.0f) * dae::ImageComponent::GetSpriteScale(),
		m_pMap->GetWorldPosition().y - static_cast<float>(m_pMap->GetTileHeight() * 0.75f * m_Row) * dae::ImageComponent::GetSpriteScale() - static_cast<float>(GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h) * dae::ImageComponent::GetSpriteScale()
	};

	if(!m_IsLeft)
	{
		spawnPos.x += static_cast<float>(m_pMap->GetTileWidth() * dae::ImageComponent::GetSpriteScale() * (m_pMap->GetNbRows() - m_Row));
	}

	GetOwner()->SetLocalPosition(spawnPos);
}
