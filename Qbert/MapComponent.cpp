#include "MapComponent.h"

#include <numeric>

#include "DiscComponent.h"
#include "GameObject.h"

qbert::MapComponent::MapComponent(dae::GameObject* pOwner, const int rows) :
BaseComponent(pOwner),
m_Rows(rows)
{
}

void qbert::MapComponent::AddTile(TileComponent* pTileComponent)
{
	m_pTiles.emplace_back(pTileComponent);
}

void qbert::MapComponent::ActivateTileAtIndex(const int index) const
{
	m_pTiles[index]->UpdateTile();
}

void qbert::MapComponent::AddDisc(DiscComponent* pDiscComponent)
{
	m_pDiscs.emplace_back(pDiscComponent);
	pDiscComponent->SetTarget(m_pTiles[m_pTiles.size() - 1]->GetStartPoint());
}

qbert::TileComponent* qbert::MapComponent::GetTileByIndex(const int index) const
{
	if (index < 0 || index >= static_cast<int>(m_pTiles.size())) return nullptr;

	return m_pTiles[index];
}

int qbert::MapComponent::GetRowFromIndex(const int index) const
{
	if (index < 0 || index >= static_cast<int>(m_pTiles.size())) return -1;

	int startingRowIndex{ 0 };
	int casesToCheck{ m_Rows };

	for(int i{0}; i < m_Rows; ++i)
	{
		if (index < startingRowIndex + casesToCheck) return i;


		startingRowIndex += casesToCheck;
		--casesToCheck;
	}


	return -1;


}

int qbert::MapComponent::GetColumnFromIndex(const int index) const
{
	const int row{ GetRowFromIndex(index) };
	const int firstIndexOfTheRow{ GetFirstIndexOfTheRow(row) };
	return row + 2 * (index - firstIndexOfTheRow);



}

int qbert::MapComponent::GetLastIndex()
{
	return static_cast<int>(m_pTiles.size()) - 1;
}

int qbert::MapComponent::GetFirstIndexOfTheRow(const int row) const
{
	if (row < 0 || row >= m_Rows) return -1;



	int firstIndexOfTheRow{0};
	int casesToCheck{ m_Rows };


	for(int i{0}; i < m_Rows; ++i)
	{
		if (row == GetRowFromIndex(firstIndexOfTheRow)) return firstIndexOfTheRow;

		firstIndexOfTheRow += casesToCheck;
		--casesToCheck;
	}

	return -1;
}

bool qbert::MapComponent::IsComplete() const
{
	for(const TileComponent* tile : m_pTiles)
	{
		if (!tile->IsCompleted()) return false;
	}
	return true;
}

int qbert::MapComponent::GetTopRightIndex(const int currentIndex) const
{
	int casesToCheck{ m_Rows - 1 };
	int rowStartingIndex{ 0 };
	for (int i{ 0 }; i < m_Rows - 1; ++i)
	{
		if (currentIndex >= rowStartingIndex && currentIndex <= rowStartingIndex + casesToCheck - 1)
		{
			return currentIndex + casesToCheck + 1;
			
		}
		rowStartingIndex += casesToCheck + 1;
		--casesToCheck;
	}

	return -1;
}
int qbert::MapComponent::GetTopLeftIndex(const int currentIndex) const
{
	int casesToCheck{ m_Rows - 1 };
	int rowStartingIndex{ 0 };
	for (int i{ 0 }; i < m_Rows - 1; ++i)
	{
		if (currentIndex >= rowStartingIndex + 1 && currentIndex <= rowStartingIndex + casesToCheck)
		{
			return currentIndex + casesToCheck;
		}
		rowStartingIndex += casesToCheck + 1;
		--casesToCheck;
	}

	return -1;
}
int qbert::MapComponent::GetBottomLeftIndex(const int currentIndex) const
{
	int casesToCheck{ m_Rows - 1 };
	int rowStartingIndex{ m_Rows };
	for (int i{ 0 }; i < m_Rows - 1; ++i)
	{
		if (currentIndex >= rowStartingIndex && currentIndex <= rowStartingIndex + casesToCheck - 1)
		{
			return currentIndex - (casesToCheck + 1);
		}
		rowStartingIndex += casesToCheck;
		--casesToCheck;
	}

	return -1;
}
int qbert::MapComponent::GetBottomRightIndex(const int currentIndex) const
{
	int casesToCheck{ m_Rows - 1 };
	int rowStartingIndex{ m_Rows };
	for (int i{ 0 }; i < m_Rows - 1; ++i)
	{
		if (currentIndex >= rowStartingIndex && currentIndex <= rowStartingIndex + casesToCheck - 1)
		{
			return currentIndex - casesToCheck;
		}
		rowStartingIndex += casesToCheck;
		--casesToCheck;
	}

	return -1;
}

int qbert::MapComponent::GetTileHeight() const
{
	return m_pTiles[0]->GetHeight();
}

int qbert::MapComponent::GetTileWidth() const
{
	return m_pTiles[0]->GetWidth();
}

bool qbert::MapComponent::IsOnATeleporter(dae::GameObject* qbert) const
{
	for (DiscComponent* pDisc : m_pDiscs)
	{
		constexpr float maxDist = 30.0f;

		const float distance = glm::length(pDisc->GetWorldPosition() - qbert->GetWorldPosition());

		if(distance <= maxDist)
		{
			pDisc->SetActive(true, qbert);

			return true;
		}
		
	}
	return false;
}

void qbert::MapComponent::SetAllTileAnimated(const bool isAnimated)
{
	for (TileComponent* tile : m_pTiles)
	{
		tile->SetAnimated(isAnimated);
	}
}

bool qbert::MapComponent::AreIndexesOnTheSameRow(const int index1, const int index2)
{
	return GetRowFromIndex(index1) == GetRowFromIndex(index2);
}

int qbert::MapComponent::GetRemainingDisks() const
{
	int nbDiscs = std::accumulate(m_pDiscs.begin(), m_pDiscs.end(), 0,
		[](int accum, DiscComponent* disc) {
			return disc->IsOwnerActive() ? accum + 1 : accum;
		});

	return nbDiscs;
}


