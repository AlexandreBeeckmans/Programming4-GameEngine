#include "CoilyMoveComponent.h"

#include "EngineTime.h"
#include "MapComponent.h"
#include "CoilyState.h"
#include "GameObject.h"


qbert::CoilyMoveComponent::CoilyMoveComponent(dae::GameObject* owner, qbert::MapComponent* pMap, QbertMoveComponent* pPlayer) :
BaseComponent(owner),
m_pMap(pMap)
{
		m_MaxDistanceX = static_cast<float>(m_pMap->GetCurrentTile()->GetWidth()) / 2.0f;
		m_pPlayer = pPlayer;

		m_State = new CoilyPreparingState{};
		m_State->Enter(*this);


}

void qbert::CoilyMoveComponent::Update()
{
	CoilyState* newState = m_State->HandleTransitions(*this);
	if (newState)
	{
		m_State->Exit(*this);
		delete m_State;
		m_State = newState;
		m_State->Enter(*this);
	}

	m_State->Update(*this);

}

void qbert::CoilyMoveComponent::Init()
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetVisible(false);
	m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint() - glm::vec2{ 0, GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h / 2 };
	m_Direction = glm::normalize(m_Target - glm::vec2{ GetWorldPosition() });
}

bool qbert::CoilyMoveComponent::HasReachedFinalPosition() const
{
	return m_AccumulatedDistanceX >= m_MaxDistanceX;
	//return glm::distance(glm::vec2(GetWorldPosition().x, GetWorldPosition().y), m_Target) <= 1.0f;
}

bool qbert::CoilyMoveComponent::IsArrived() const
{
	const glm::vec2 currentPos
	{
		GetOwner()->GetWorldPosition().x,
		GetOwner()->GetWorldPosition().y
	};
	return glm::length(m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint() - currentPos) < 30.0f;
}

void qbert::CoilyMoveComponent::ResetPositionValues()
{
	m_AccumulatedDistanceX = 0;
	m_AdditionalY = 0;

	if (m_pMap->GetTileByIndex(m_CurrentIndex))
		GetOwner()->SetLocalPosition(m_Target);
		//GetOwner()->SetLocalPosition(m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint());
}

void qbert::CoilyMoveComponent::Bounce()
{
	constexpr float jumpSpeed{ 50.0f };
	m_AdditionalY = jumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime();

	if (m_AccumulatedDistanceX > m_MaxDistanceX / 2.0f)
	{
		m_AdditionalY *= -1;
	}

	const glm::vec2 jumpDirection
	{
	0,
		-m_AdditionalY
	};

	GetOwner()->Translate(jumpSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * jumpDirection);
}

void qbert::CoilyMoveComponent::SetMovementDirection()
{
	const int playerRow = m_pMap->GetRowFromIndex(m_pPlayer->GetCurrentIndex());
	const int playerColumn = m_pMap->GetColumnFromIndex(m_pPlayer->GetCurrentIndex());

	const int coilyRow = m_pMap->GetRowFromIndex(m_CurrentIndex);
	const int coilyColumn = m_pMap->GetColumnFromIndex(m_CurrentIndex);


	if(playerRow < coilyRow)
	{
		if(playerColumn < coilyColumn)
		{
			m_CurrentIndex = m_pMap->GetBottomLeftIndex(m_CurrentIndex);
			//m_Direction = { -0.5f, 0.75f };
			GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(9);
			//return;
		}
		else
		{
			m_CurrentIndex = m_pMap->GetBottomRightIndex(m_CurrentIndex);
			GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(7);
			//m_Direction = { 0.5f, 0.75f };
			//return;
		}

		
	}
	else if(playerColumn < coilyColumn)
	{
		m_CurrentIndex = m_pMap->GetTopLeftIndex(m_CurrentIndex);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(5);
		//m_Direction = { -0.5f, -0.75f };
		//return;
	}
	else
	{
		m_CurrentIndex = m_pMap->GetTopRightIndex(m_CurrentIndex);
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(3);
		//m_Direction = { 0.5f, -0.75f };
	}



	if(m_CurrentIndex < 0)
	{
		/*GetOwner()->SetActive(false);
		GetOwner()->SetVisible(false);*/
		return;
	}

	m_Target = m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint() - glm::vec2{0, GetOwner()->GetComponent<dae::ImageComponent>()->GetShape().h/2};
	m_Direction = glm::normalize(m_Target - glm::vec2{ GetOwner()->GetWorldPosition() });
}

void qbert::CoilyMoveComponent::SetWaitingSprite() const
{
	const int currentCol{ GetOwner()->GetComponent<dae::ImageComponent>()->GetColumn() };

	if(currentCol > 0)
	{
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(currentCol-1);
	}
	else
	{
		GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(2);
	}
		
}

void qbert::CoilyMoveComponent::SetArrivingSprite(const int column) const
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetColumn(column);
}

void qbert::CoilyMoveComponent::SetVisible() const
{
	GetOwner()->GetComponent<dae::ImageComponent>()->SetVisible(true);
}

void qbert::CoilyMoveComponent::UpdateMovement()
{
	Bounce();
	constexpr float speed{ 55.0f };
	//const glm::vec2 direction = glm::normalize(m_Target - glm::vec2(GetWorldPosition().x, GetWorldPosition().y));


	/*GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
	m_AccumulatedDistanceX += speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);*/
	GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
	m_AccumulatedDistanceX += speed * dae::EngineTime::GetInstance().GetDeltaTime() * std::abs(m_Direction.x);
}

void qbert::CoilyMoveComponent::CheckForPlayer() const
{
	if (m_pPlayer->GetCurrentIndex() == m_CurrentIndex)
	{
		m_pPlayer->EncountersEnemy();
	}
}

void qbert::CoilyMoveComponent::UpdateArrivingMovement() const
{
	constexpr float speed = 55.0f;
	/*const glm::vec2 currentPos
	{
		GetOwner()->GetWorldPosition().x,
		GetOwner()->GetWorldPosition().y
	};*/

	//const glm::vec2 direction = glm::normalize(m_pMap->GetTileByIndex(m_CurrentIndex)->GetStartPoint() - currentPos);
	GetOwner()->Translate(speed * dae::EngineTime::GetInstance().GetDeltaTime() * m_Direction);
}
