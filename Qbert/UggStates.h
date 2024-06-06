#pragma once
#include "State.hpp"

namespace qbert
{
	class UggDirectionComponent;
}

namespace qbert
{
	class GridMoveComponent;
	class FallComponent;
	class KillerComponent;
	class DeadFallComponent;


	class UggState : public dae::State<UggState>
	{
	public:
		virtual void Enter(dae::GameObject& coilyObject);

	protected:
		GridMoveComponent* GetMoveComponent()const { return m_pMoveComponent; }
		FallComponent* GetFallComponent() const { return m_pFallComponent; }
		KillerComponent* GetKillerComponent()const { return m_pKillerComponent; }
		DeadFallComponent* GetDeadFallComponent()const { return m_pDeadFallComponent; }
		UggDirectionComponent* GetDirectionComponent()const { return m_pDirectionComponent; }

	private:
		GridMoveComponent* m_pMoveComponent{};
		FallComponent* m_pFallComponent{};
		KillerComponent* m_pKillerComponent{};
		DeadFallComponent* m_pDeadFallComponent{};
		UggDirectionComponent* m_pDirectionComponent;
	};

	class UggArrivingState final : public UggState
	{
	public:
		virtual std::unique_ptr<UggState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;


	private:
		float m_CurrentAnimTime = 0.0f;
		static constexpr  float m_MaxAnimTime{ 0.5f };
		int m_AnimState{ 0 };
	};

	class UggPreparingState final : public UggState
	{
	public:
		virtual std::unique_ptr<UggState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;

	private:
		float m_CurrentPreparingTime = 0.0f;
		static constexpr float m_MaxPreparingTime{ 3.0f };
	};

	class UggWaitingState final : public UggState
	{
	public:
		virtual std::unique_ptr<UggState> HandleTransitions() override;
		virtual void Update() override;

	private:
		float m_CurrentPreparingTime = 0.0f;
		static constexpr float m_MaxWaitingTime{ 1.5f };
	};

	class UggMovingState final : public UggState
	{
	public:
		virtual std::unique_ptr<UggState> HandleTransitions() override;
		virtual void Update() override;
		virtual void Enter(dae::GameObject& coilyObject) override;
	};

	class UggDyingState final : public UggState
	{
	public:
		virtual std::unique_ptr<UggState> HandleTransitions() override;
		virtual void Update() override;

	private:
		float m_CurrentDyingTime = 0.0f;
		static constexpr float m_MaxDyingTime{ 6.0f };
	};


}


