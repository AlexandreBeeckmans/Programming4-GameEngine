#pragma once
#include "TextComponent.h"

#include <memory>

namespace dae
{
	class FPSComponent;


	class RenderFPSComponent final : public TextComponent
	{
	public:

		RenderFPSComponent(GameObject* pGameObject, std::shared_ptr<Font> pFont);
		~RenderFPSComponent() = default;
		void virtual Update() override;

		RenderFPSComponent(const RenderFPSComponent& other) = default;
		RenderFPSComponent(RenderFPSComponent&& other) = default;
		RenderFPSComponent& operator=(const RenderFPSComponent& other) = default;
		RenderFPSComponent& operator=(RenderFPSComponent&& other) = default;


	private:
		FPSComponent* m_pFPSComponent{};

		const float m_TimeToRender{ 0.5f };

		float m_AccumulatedTime{ 0.0f };
		float m_AccumulatedFPS{ 0.0f };
		int m_IterationCount{ 0 };
	};
}


