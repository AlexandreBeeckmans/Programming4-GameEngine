#include "AnimatorComponent.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "ImageComponent.h"

dae::AnimatorComponent::AnimatorComponent(GameObject* pGameObject, const bool isActive, const float frameTime, const int nbCols, const int nbRows, const int startCol, const int startRow):
BaseComponent(pGameObject),
m_NbCols(nbCols),
m_NbRows(nbRows),
m_FrameTime(frameTime),
m_StartCol(startCol),
m_StartRow(startRow),
m_CurrentCol(m_StartCol),
m_CurrentRow(m_StartRow),
m_IsActive(isActive)
{
	m_pImage = GetOwner()->GetComponent<dae::ImageComponent>();
}

void dae::AnimatorComponent::Update()
{
	if (!m_IsActive) return;
	m_AccumulatedTime += EngineTime::GetInstance().GetDeltaTime();

	if(m_AccumulatedTime >= m_FrameTime)
	{
		m_AccumulatedTime = 0;

		++m_CurrentCol;
		if(m_CurrentCol >= m_NbCols + m_StartCol)
		{
			m_CurrentCol = m_StartCol;
			++m_CurrentRow;
			if(m_CurrentRow >= m_NbRows + m_StartRow)
			{
				m_CurrentRow = m_StartRow;
			}
			m_pImage->SetRow(m_CurrentRow);
		}
		m_pImage->SetColumn(m_CurrentCol);
	}
}

void dae::AnimatorComponent::SetActive(const bool isActive)
{
	m_IsActive = isActive;
}
