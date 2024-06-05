#pragma once
#include "GameObject.h"

namespace dae
{
	template<typename BaseState>
	class State
	{
	public:
		virtual ~State() = default;

		virtual std::unique_ptr<BaseState> HandleTransitions() { return nullptr; }
		virtual void Update() {}
		virtual void Enter() {};
		virtual void Exit() {}
	};
}


