#pragma once
#include "CoilyMoveComponent.h"

namespace qbert
{
	class CoilyState
	{
	public:
		virtual ~CoilyState() {}

		virtual CoilyState* HandleTransitions(const CoilyMoveComponent&) { return nullptr; }
		virtual void Update(CoilyMoveComponent&) {}
		virtual void Enter(CoilyMoveComponent&) {}
		virtual void Exit(CoilyMoveComponent&) {}
	};

	class CoilyWaitingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions(const CoilyMoveComponent&) override;
		virtual void Update(CoilyMoveComponent&) override;
		virtual void Enter(CoilyMoveComponent&) override;

	private:
		float m_CurrentWaitingTime = 0.0f;
		const float m_MaxWaitingTime{ 2.0f };
		
	};

	class CoilyJumpingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions(const CoilyMoveComponent&) override;
		virtual void Update(CoilyMoveComponent&) override;
		virtual void Enter(CoilyMoveComponent&) override;
	};

	class CoilyArrivingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions(const CoilyMoveComponent&) override;
		virtual void Update(CoilyMoveComponent&) override;
		virtual void Enter(CoilyMoveComponent&) override;

	private:
		float m_CurrentAnimTime = 0.0f;
		const float m_MaxAnimTime{ 0.5f };
		int m_AnimState{ 0 };
	};

	class CoilyPreparingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions(const CoilyMoveComponent&) override;
		virtual void Update(CoilyMoveComponent&) override;

	private:
		float m_CurrentPreparingTime = 0.0f;
		const float m_MaxAnimTime{ 10.0f };
	};
}


