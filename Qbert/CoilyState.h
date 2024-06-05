#pragma once
#include "GameObject.h"


namespace qbert
{
	class InputDirectionComponent;
}

namespace qbert
{
	class CoilyFSMManagerComponent;
	class GridMoveComponent;
	class FallComponent;
	class FollowPlayerComponent;
	class CoilyAnimatorComponent;
	class KillerComponent;

	class CoilyState
	{
	public:
		virtual ~CoilyState() {}

		virtual std::unique_ptr<CoilyState> HandleTransitions() { return nullptr; }
		virtual void Update() {}
		virtual void Enter(dae::GameObject& coilyObject);
		virtual void Exit() {}

	protected:
		CoilyFSMManagerComponent* GetCoilyComponent()const { return m_pCoilyComponent; }
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
		FallComponent* GetFallComponent() const { return m_pFallComponent; }
		FollowPlayerComponent* GetFollowComponent() const { return m_pFollowPlayerComponent; }
		KillerComponent* GetKillerComponent()const { return m_pKillerComponent; }
		CoilyAnimatorComponent* GetAnimatorComponent()const { return m_pAnimatorComponent; }
		InputDirectionComponent* GetInputComonent()const { return m_pInputComponent; }

	private:
		CoilyFSMManagerComponent* m_pCoilyComponent{};
		GridMoveComponent* m_pMoveComponent{};
		FallComponent* m_pFallComponent{};
		FollowPlayerComponent* m_pFollowPlayerComponent{};
		KillerComponent* m_pKillerComponent{};
		CoilyAnimatorComponent* m_pAnimatorComponent{};
		InputDirectionComponent* m_pInputComponent{};
	};

	class CoilyWaitingState final : public CoilyState
	{
	public:
		virtual std::unique_ptr<CoilyState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;

	private:
		float m_CurrentWaitingTime{ 0.0f };
		static constexpr float m_MaxWaitingTime{ 1.0f };
		
	};

	class CoilyJumpingState final : public CoilyState
	{
	public:
		virtual std::unique_ptr<CoilyState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;
	};

	class CoilyArrivingState final : public CoilyState
	{
	public:
		virtual std::unique_ptr<CoilyState> HandleTransitions() override;
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
		virtual std::unique_ptr<CoilyState> HandleTransitions() override;
		virtual void Update() override;

	private:
		float m_CurrentPreparingTime = 0.0f;
		static constexpr float m_MaxAnimTime{ 1.0f };
	};
}


