#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "CoilyState.h"

namespace qbert
{
	
}

namespace qbert
{
	class CoilyState;
	class GridMoveComponent;
	class MapComponent;
	class QbertMoveComponent;
	class KillableComponent;

	class CoilyFSMManagerComponent final : public dae::BaseComponent
	{
	public:
		CoilyFSMManagerComponent(dae::GameObject* owner);
	virtual ~CoilyFSMManagerComponent() override = default;


		CoilyFSMManagerComponent(const CoilyFSMManagerComponent& other) = delete;
		CoilyFSMManagerComponent(CoilyFSMManagerComponent&& other) = delete;
		CoilyFSMManagerComponent& operator=(const CoilyFSMManagerComponent& other) = delete;
		CoilyFSMManagerComponent& operator=(CoilyFSMManagerComponent&& other) = delete;

		void Update() override;

private:
		std::unique_ptr<CoilyState> m_State{ nullptr };
	};
}


