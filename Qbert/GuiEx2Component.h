#pragma once
#include "BaseGuiComponent.h"
#include "Graph.hpp"
#include <memory>

namespace dae
{
	class GameObject;

	class GuiEx2Component final : public BaseGuiComponent
	{
	public:
		GuiEx2Component(GameObject* pParent);


		void virtual RenderGui() const override;
	private:

		std::unique_ptr<dae::Graph<TrashGameObject>> m_GOGraph{};
		std::unique_ptr<dae::Graph<TrashGameObjectAlt>> m_GOAltGraph{};

		void DisplayCombinedGraph(ImU32* colors) const;
	};
}

