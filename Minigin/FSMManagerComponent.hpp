#pragma once
#include <memory>
#include <type_traits>
#include "State.hpp"

#include "BaseComponent.h"

namespace dae
{
	template <typename BaseState, typename StartState,
		typename = std::enable_if_t<std::is_base_of_v<State<BaseState>, BaseState>&& std::is_base_of_v<BaseState, StartState>>>
	class FSMManagerComponent final : public BaseComponent
	{
	public:
		FSMManagerComponent(dae::GameObject* owner);
		virtual ~FSMManagerComponent() override = default;


		FSMManagerComponent(const FSMManagerComponent& other) = delete;
		FSMManagerComponent(FSMManagerComponent&& other) = delete;
		FSMManagerComponent& operator=(const FSMManagerComponent& other) = delete;
		FSMManagerComponent& operator=(FSMManagerComponent&& other) = delete;

		void virtual Init() override;
		void virtual Update() override;

	private:
		std::unique_ptr<BaseState> m_State{ nullptr };
	};
}

namespace dae
{
	template <typename BaseState, typename StartState, typename Constraints>
	FSMManagerComponent<BaseState, StartState, Constraints>::FSMManagerComponent(GameObject* owner) :
		BaseComponent(owner)
	{
		static_assert(std::is_base_of_v<State<BaseState>, BaseState>, "BaseState must inherit from State<BaseState>");
		static_assert(std::is_base_of_v<BaseState, StartState>, "StartState must inherit from BaseState");
		m_State = std::make_unique<StartState>();
	}

	template <typename BaseState, typename StartState, typename Constraints>
	void dae::FSMManagerComponent<BaseState, StartState, Constraints>::Init()
	{
		m_State->Enter(*GetOwner());
	}

	template <typename BaseState, typename StartState, typename Constraints>
	void dae::FSMManagerComponent<BaseState, StartState, Constraints>::Update()
	{
		std::unique_ptr<BaseState> pNewState = m_State->HandleTransitions();
		if (pNewState)
		{
			m_State->Exit();
			m_State = std::move(pNewState);
			m_State->Enter(*GetOwner());
		}

		m_State->Update();

	}

}


