#include "MapComponent.h"

qbert::MapComponent::MapComponent(dae::GameObject* pOwner) :
BaseComponent(pOwner)
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
	if(m_CurrentTileIndex >= 0 && m_CurrentTileIndex < static_cast<int>(m_pTiles.size()))
	{
		return m_pTiles[m_CurrentTileIndex];
	}
	return nullptr;
}

void qbert::MapComponent::SetCurrentIndexToLast()
{
	m_CurrentTileIndex = static_cast<int>(m_pTiles.size()) - 1;
}

void qbert::MapComponent::SetTopRightTile()
{
	if (m_CurrentTileIndex >= 0 && m_CurrentTileIndex <= 5)
	{
		m_CurrentTileIndex += 7;
		return;
	}
	if (m_CurrentTileIndex >= 7 && m_CurrentTileIndex <= 11)
	{
		m_CurrentTileIndex += 6;
		return;
	}
	if (m_CurrentTileIndex >= 13 && m_CurrentTileIndex <= 16)
	{
		m_CurrentTileIndex += 5;
		return;
	}
	if (m_CurrentTileIndex >= 18 && m_CurrentTileIndex <= 20)
	{
		m_CurrentTileIndex += 4;
		return;
	}
	if (m_CurrentTileIndex == 22 || m_CurrentTileIndex == 23)
	{
		m_CurrentTileIndex += 3;
		return;
	}
	if (m_CurrentTileIndex == 25)
	{
		m_CurrentTileIndex += 2;
		return;
	}
	m_CurrentTileIndex = -1;
}

void qbert::MapComponent::SetBottomLeft()
{
	if (m_CurrentTileIndex >= 7 && m_CurrentTileIndex <= 12)
	{
		m_CurrentTileIndex -= 7;
		return;
	}

	if (m_CurrentTileIndex >= 13 && m_CurrentTileIndex <= 17)
	{
		m_CurrentTileIndex -= 6;
		return;
	}

	if (m_CurrentTileIndex >= 18 && m_CurrentTileIndex <= 21)
	{
		m_CurrentTileIndex -= 5;
		return;
	}

	if (m_CurrentTileIndex >= 22 && m_CurrentTileIndex <= 24)
	{
		m_CurrentTileIndex -= 4;
		return;
	}

	if (m_CurrentTileIndex == 25 || m_CurrentTileIndex == 26)
	{
		m_CurrentTileIndex -= 3;
		return;
	}
	if (m_CurrentTileIndex == 27)
	{
		m_CurrentTileIndex -= 2;
		return;
	}

	m_CurrentTileIndex = -1;
}

void qbert::MapComponent::SetBottomRight()
{
	if (m_CurrentTileIndex >= 7 && m_CurrentTileIndex <= 12)
	{
		m_CurrentTileIndex -= 6;
		return;
	}

	if (m_CurrentTileIndex >= 13 && m_CurrentTileIndex <= 17)
	{
		m_CurrentTileIndex -= 5;
		return;
	}

	if (m_CurrentTileIndex >= 18 && m_CurrentTileIndex <= 21)
	{
		m_CurrentTileIndex -= 4;
		return;
	}

	if (m_CurrentTileIndex >= 22 && m_CurrentTileIndex <= 24)
	{
		m_CurrentTileIndex -= 3;
		return;
	}

	if (m_CurrentTileIndex == 25 || m_CurrentTileIndex == 26)
	{
		m_CurrentTileIndex -= 2;
		return;
	}
	if (m_CurrentTileIndex == 27)
	{
		m_CurrentTileIndex -= 1;
		return;
	}

	m_CurrentTileIndex = -1;
}

bool qbert::MapComponent::IsComplete() const
{
	for(const TileComponent* tile : m_pTiles)
	{
		if (!tile->IsCompleted()) return false;
	}
	return true;
}

void qbert::MapComponent::SetTopLeftTile()
{
	if(m_CurrentTileIndex >= 1 && m_CurrentTileIndex <= 6)
	{
		m_CurrentTileIndex += 6;
		return;
	}

	if(m_CurrentTileIndex >=8 && m_CurrentTileIndex <= 12)
	{
		m_CurrentTileIndex += 5;
		return;
	}

	if(m_CurrentTileIndex >= 14 && m_CurrentTileIndex <= 17)
	{
		m_CurrentTileIndex += 4;
		return;
	}

	if(m_CurrentTileIndex >= 19 && m_CurrentTileIndex <= 21)
	{
		m_CurrentTileIndex += 3;
		return;
	}

	if(m_CurrentTileIndex == 23 || m_CurrentTileIndex == 24)
	{
		m_CurrentTileIndex += 2;
		return;
	}

	if(m_CurrentTileIndex == 26)
	{
		m_CurrentTileIndex += 1;
		return;
	}

	m_CurrentTileIndex = -1;
}
