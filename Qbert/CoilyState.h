#pragma once
#include "GameObject.h"

//#include "CoilyMoveComponent.h"

namespace qbert
{
	class CoilyMoveComponent;
	class GridMoveComponent;

	class CoilyState
	{
	public:
		virtual ~CoilyState() {}

		virtual CoilyState* HandleTransitions() { return nullptr; }
		virtual void Update() {}
		virtual void Enter(dae::GameObject& coilyObject);
		virtual void Exit() {}

	protected:
		CoilyMoveComponent* GetCoilyComponent()const { return m_pCoilyComponent; }
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
	private:
		CoilyMoveComponent* m_pCoilyComponent{};
		GridMoveComponent* m_pMoveComponent{};
	};

	class CoilyWaitingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;

	private:
		float m_CurrentWaitingTime{ 0.0f };
		static constexpr float m_MaxWaitingTime{ 1.0f };
		
	};

	class CoilyJumpingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;
	};

	class CoilyArrivingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;

	private:
		float m_CurrentAnimTime = 0.0f;
		static constexpr  float m_MaxAnimTime{ 0.5f };
		int m_AnimState{ 0 };
	};

	class CoilyPreparingState final : public CoilyState
	{
	public:
		virtual CoilyState* HandleTransitions() override;
		virtual void Update() override;

	private:
		float m_CurrentPreparingTime = 0.0f;
		static constexpr float m_MaxAnimTime{ 1.0f };
	};
}


