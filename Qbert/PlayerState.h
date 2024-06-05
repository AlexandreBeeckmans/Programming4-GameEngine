#pragma once
#include "GameObject.h"
#include "State.hpp"


namespace dae
{
	class HealthComponent;
}

namespace qbert
{
	class QbertJumpAnimatorComponent;
	class QbertFSMManagerComponent;
	class GridMoveComponent;
	class FallComponent;
	class InputDirectionComponent;
	class KillableComponent;
	class TileActivatorComponent;

	class PlayerState : public dae::State<PlayerState>
	{
	public:
		virtual void Enter(dae::GameObject& qbertObject);

	protected:
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
		FallComponent* GetFallComponent() const { return m_pFallComponent; }
		InputDirectionComponent* GetInputComponent() const { return m_pInputComponent; }
		KillableComponent* GetKillableComponent() const { return m_pKillableComponent; }
		TileActivatorComponent* GetTileActivatorComponent() const { return m_pTileActivatorComponent; }
		QbertJumpAnimatorComponent* GetJumpAnimator() const { return m_pJumpAnimator; }

		dae::HealthComponent* GetHealthComponent()const { return m_pHealthComponent; }
	private:
		GridMoveComponent* m_pMoveComponent{};
		FallComponent* m_pFallComponent{};
		InputDirectionComponent* m_pInputComponent{};
		KillableComponent* m_pKillableComponent{};
		TileActivatorComponent* m_pTileActivatorComponent{};
		QbertJumpAnimatorComponent* m_pJumpAnimator{};

		dae::HealthComponent* m_pHealthComponent{};
	};

	class WaitingState final : public PlayerState
	{
	public:
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbertObject) override;
	};

	class JumpingState final : public PlayerState
	{
	public:
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Exit() override;
	};

	class DieState final : public PlayerState
	{
	public:
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
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
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Update() override;
	private:
		float m_CurrentWinTime = 0.0f;
		float m_MaxWinTime = 5.0f;
	};

	class TeleportingState final : public PlayerState
	{
	public:
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
		
	};

	class FallingState final : public PlayerState
	{
	public:
		virtual std::unique_ptr<PlayerState> HandleTransitions() override;
		virtual void Enter(dae::GameObject& qbert) override;
		virtual void Update() override;

	};
}


