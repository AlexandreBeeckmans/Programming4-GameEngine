#pragma once
#include "GameObject.h"

namespace dae
{
	class HealthComponent;
}

namespace qbert
{
	class QbertMoveComponent;
	class GridMoveComponent;

	class PlayerState
	{
	public:
		virtual ~PlayerState(){}

		virtual PlayerState* HandleTransitions() { return nullptr; }

		virtual void Update(){}
		virtual void Enter(dae::GameObject& qbertObject);
		virtual void Exit() {}

	protected:
		QbertMoveComponent* GetQbertComponent()const{ return m_pQbertComponent; }
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
		dae::HealthComponent* GetHealthComponent()const { return m_pHealthComponent; }
	private:
		QbertMoveComponent* m_pQbertComponent{};
		GridMoveComponent* m_pMoveComponent{};
		dae::HealthComponent* m_pHealthComponent{};
	};

	class WaitingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbertObject) override;
	};

	class JumpingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& qbert) override;
	};

	class DieState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Exit() override;

	private:
		float m_CurrentDeadTime = 0.0f;
		float m_MaxDeadTime = 5.0f;
	};

	class WinState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Update() override;
	private:
		float m_CurrentWinTime = 0.0f;
		float m_MaxWinTime = 5.0f;
	};

	class TeleportingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		
	};

	class FallingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Update() override;

	};
}


