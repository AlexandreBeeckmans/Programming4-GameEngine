#include "MapComponent.h"

qbert::MapComponent::MapComponent(dae::GameObject* pOwner, const int rows) :
BaseComponent(pOwner),
m_Rows(rows)
{
}

void qbert::MapComponent::AddTile(TileComponent* pTileComponent)
{
	m_pTiles.emplace_back(pTileComponent);
}

void qbert::MapComponent::SetNextTile(QbertDirection direction)
{
	switch(direction)
	{
	case QbertDirection::TOPLEFT:
		{
			SetTopLeftTile();
			break;
		}
	case QbertDirection::TOPRIGHT:
		{
			SetTopRightTile();
			break;
		}
	case QbertDirection::BOTTOMLEFT:
		{
			SetBottomLeft();
			break;
		}
	case QbertDirection::BOTTOMRIGHT:
		{
			SetBottomRight();
			break;
		}
	}
	
}

void qbert::MapComponent::ActivateCurrentTile() const
{
	m_pTiles[m_CurrentTileIndex]->UpdateTile();
}
qbert::TileComponent* qbert::MapComponent::GetCurrentTile() const
{
	return GetTileByIndex(m_CurrentTileIndex);
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

void qbert::MapComponent::SetCurrentIndexToLast()
{
	m_CurrentTileIndex = static_cast<int>(m_pTiles.size()) - 1;
}

void qbert::MapComponent::SetTopRightTile()
{
	m_CurrentTileIndex = GetTopRightIndex(m_CurrentTileIndex);
}
void qbert::MapComponent::SetBottomLeft()
{
	m_CurrentTileIndex = GetBottomLeftIndex(m_CurrentTileIndex);
}
void qbert::MapComponent::SetBottomRight()
{
	m_CurrentTileIndex = GetBottomRightIndex(m_CurrentTileIndex);
	
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

void qbert::MapComponent::SetTopLeftTile()
{
	m_CurrentTileIndex = GetTopLeftIndex(m_CurrentTileIndex);
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


