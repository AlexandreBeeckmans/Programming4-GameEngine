#pragma once
#include "BaseGuiComponent.h"
#include "Graph.hpp"
#include <memory>

namespace dae
{
	class GameObject;

	class GuiEx1Component final : public BaseGuiComponent
	{
	public:
		GuiEx1Component(GameObject* pParent);


		void virtual RenderGui() const override;
	private:

		std::unique_ptr<dae::Graph<int>> m_IntGraph{};
	};
}


