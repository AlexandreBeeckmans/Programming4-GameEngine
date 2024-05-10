#pragma once
#include "QbertMoveComponent.h"

namespace qbert
{
	class PlayerState
	{
	public:
		virtual ~PlayerState(){};

		virtual PlayerState* HandleTransitions(const QbertMoveComponent&) { return nullptr; }
		virtual void Update(QbertMoveComponent&){}
		virtual void Enter(QbertMoveComponent&){}
		virtual void Exit(QbertMoveComponent&) {}

	};

	class WaitingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions(const QbertMoveComponent& qbert) override;
		virtual void Enter(QbertMoveComponent& qbert) override;
	};

	class JumpingState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions(const QbertMoveComponent& qbert) override;
		virtual void Update(QbertMoveComponent& qbert) override;
		virtual void Enter(QbertMoveComponent& qbert) override;
	};

	class DieState final : public PlayerState
	{
	public:
		virtual PlayerState* HandleTransitions(const QbertMoveComponent& qbert) override;
		virtual void Update(QbertMoveComponent& qbert) override;
		virtual void Enter(QbertMoveComponent& qbert) override;
		virtual void Exit(QbertMoveComponent&) override;

	private:
		float m_CurrentDeadTime = 0.0f;
		float m_MaxDeadTime = 5.0f;
	};

	class WinState final : public PlayerState
	{
	public:
		virtual void Enter(QbertMoveComponent& qbert) override;
	};
}


