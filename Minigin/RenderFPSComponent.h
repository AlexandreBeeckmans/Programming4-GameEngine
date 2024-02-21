#pragma once
#include "BaseComponent.h"

#include <memory>

namespace dae
{
	class FPSComponent;
	class TextComponent;


	class RenderFPSComponent final : public BaseComponent
	{
	public:

		RenderFPSComponent(GameObject* pGameObject);
		~RenderFPSComponent() = default;

		void virtual Update(const float deltaTime) override;
		void virtual Render() const override;

		RenderFPSComponent(const RenderFPSComponent& other) = default;
		RenderFPSComponent(RenderFPSComponent&& other) = default;
		RenderFPSComponent& operator=(const RenderFPSComponent& other) = default;
		RenderFPSComponent& operator=(RenderFPSComponent&& other) = default;


	private:
		std::shared_ptr<FPSComponent> m_pFPSComponent{};
		std::shared_ptr<TextComponent> m_pTextComponent{};

		const float m_TimeToRender{ 0.5f };
		float m_AccumulatedTime{ 0.4f };
	};
}


