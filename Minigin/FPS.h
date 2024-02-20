#pragma once

#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final: public BaseComponent
	{

	public:

		FPSComponent() = default;
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = default;
		FPSComponent(FPSComponent&& other) = default;
		FPSComponent& operator=(const FPSComponent& other) = default;
		FPSComponent& operator=(FPSComponent&& other) = default;


		void Update(const float deltaTime) override;
		float GetFPS() { return m_Fps; };

	private:
		float m_Fps{ 0 };
	};
}

