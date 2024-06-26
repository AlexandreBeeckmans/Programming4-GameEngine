#pragma once
#include <memory>

#include "GameObject.h"
#include "State.hpp"

namespace qbert
{
	class DeadFallComponent;
	class PlayerKillableComponent;
	class TileDeactivatorComponent;
	class GridMoveComponent;
	class SlickDirection;
	class FallComponent;
	class SlickAnimatorComponent;

	class SlickState : public dae::State<SlickState>
	{
	public:

		virtual void Enter(dae::GameObject& slickObject);

	protected:
		FallComponent* GetFallComponent()const { return m_pFallComponent; }
		SlickDirection* GetDirectionComponent()const { return m_pDirectionComponent; }
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
		TileDeactivatorComponent* GetDeactivatorComponent() const { return m_pDeactivatorComponent; }
		PlayerKillableComponent* GetKillableComponent() const { return m_pKillableComponent; }
		DeadFallComponent* GetDeadFallComponent() const { return m_pDeadFallComponent; }
		SlickAnimatorComponent* GetAnimatorComponent()const { return m_pAnimatorComponent; }

	private:
		FallComponent* m_pFallComponent{nullptr};
		SlickDirection* m_pDirectionComponent{ nullptr };
		GridMoveComponent* m_pMoveComponent{ nullptr };
		TileDeactivatorComponent* m_pDeactivatorComponent{ nullptr };
		PlayerKillableComponent* m_pKillableComponent{ nullptr };
		DeadFallComponent* m_pDeadFallComponent{ nullptr };
		SlickAnimatorComponent* m_pAnimatorComponent{ nullptr };
	};

	class SlickPreparingState final : public SlickState
	{
	public:
		virtual std::unique_ptr<SlickState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& slickObject) override;

	private:
		float m_CurrentPreparingTime{ 0.0f };
		float m_PreparingTime{ 0.0f };

		static constexpr float m_MaxPreparingTime{ 8.0f };
	};

	class SlickFallingState final : public SlickState
	{
	public:
		virtual std::unique_ptr<SlickState> HandleTransitions() override;
		virtual void Update() override;

		virtual void Enter(dae::GameObject& slickObject) override;
	};

	class SlickWaitingState final : public SlickState
	{
	public:
		virtual std::unique_ptr<SlickState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& slickObject) override;

	private:
		float m_CurrentWaitingTime{ 0.0f };
		float m_WaitingTime{ 0.0f };

		static constexpr float m_MaxWaitingTime{ 0.5f };


	};

	class SlickJumpingState final : public SlickState
	{
	public:
		virtual std::unique_ptr<SlickState> HandleTransitions() override;
		virtual void Update() override;

		virtual void Enter(dae::GameObject& slickObject) override;
	};

	class SlickDyingState final : public SlickState
	{
	public:
		virtual std::unique_ptr<SlickState> HandleTransitions() override;
		virtual void Enter(dae::GameObject& slickObject) override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}


