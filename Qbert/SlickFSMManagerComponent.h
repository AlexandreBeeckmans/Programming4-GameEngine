#pragma once
#include <memory>

#include "BaseComponent.h"
#include "SlickState.h"

namespace qbert
{

	class SlickFSMManagerComponent final : public dae::BaseComponent
	{
	public:
		SlickFSMManagerComponent(dae::GameObject* owner);
		virtual ~SlickFSMManagerComponent() override = default;


		SlickFSMManagerComponent(const SlickFSMManagerComponent& other) = delete;
		SlickFSMManagerComponent(SlickFSMManagerComponent&& other) = delete;
		SlickFSMManagerComponent& operator=(const SlickFSMManagerComponent& other) = delete;
		SlickFSMManagerComponent& operator=(SlickFSMManagerComponent&& other) = delete;

		void virtual Init() override;
		void virtual Update() override;

	private:
		std::unique_ptr<SlickState> m_State{ nullptr };
	};
}
