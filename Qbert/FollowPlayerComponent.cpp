#include "FollowPlayerComponent.h"

#include "GameObject.h"
#include "GridMoveComponent.h"
#include "MapComponent.h"

qbert::FollowPlayerComponent::FollowPlayerComponent(dae::GameObject* owner, std::vector<std::unique_ptr<dae::GameObject>>* pPlayers,
	MapComponent* pMap):
BaseComponent(owner),
m_pMap(pMap)
{
	for (auto& player : *pPlayers)
	{
		m_pPlayerMoveComponents.push_back(player->GetComponent<GridMoveComponent>());
	}
}

void qbert::FollowPlayerComponent::Init()
{
	m_pMoveComponent = GetOwner()->GetComponent<GridMoveComponent>();
}

void qbert::FollowPlayerComponent::SetMovementDirection() const
{
	const int coilyRow = m_pMap->GetRowFromIndex(m_pMoveComponent->GetCurrentIndex());
	const int coilyColumn = m_pMap->GetColumnFromIndex(m_pMoveComponent->GetCurrentIndex());

	std::vector<int> distances;
	for (auto move : m_pPlayerMoveComponents)
	{
		if (!move->IsOwnerActive())
		{
			distances.push_back(INT16_MAX);
			continue;
		}
		const int playerRow = m_pMap->GetRowFromIndex(move->GetCurrentIndex());
		const int playerColumn = m_pMap->GetColumnFromIndex(move->GetCurrentIndex());

		const int rowDistance{ std::abs(coilyRow - playerRow) };
		const int columnDistance{ std::abs(coilyColumn - playerColumn) };
		distances.push_back(rowDistance + columnDistance);
	}

	auto minDistance{ std::ranges::min_element(distances) };
	auto playerToFollowIndex = std::distance(distances.begin(), minDistance);


	
	if (m_pPlayerMoveComponents[playerToFollowIndex]->GetCurrentIndex() == -1) return;

	const int finalRow = m_pMap->GetRowFromIndex(m_pPlayerMoveComponents[playerToFollowIndex]->GetCurrentIndex());
	const int finalColumn = m_pMap->GetColumnFromIndex(m_pPlayerMoveComponents[playerToFollowIndex]->GetCurrentIndex());

	if (finalRow < coilyRow)
	{
		if (finalColumn < coilyColumn)
		{
			m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMLEFT);
			return;
		}
		m_pMoveComponent->SetGridDirection(GridDirection::BOTTOMRIGHT);
		return;


	}

	if (finalColumn < coilyColumn)
	{
		m_pMoveComponent->SetGridDirection(GridDirection::TOPLEFT);
		return;
	}

	m_pMoveComponent->SetGridDirection(GridDirection::TOPRIGHT);
}
