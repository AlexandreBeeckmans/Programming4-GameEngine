#pragma once

#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final: public BaseComponent
	{

	public:
		void Update(const float deltaTime) override;
		float GetFPS() { return m_Fps; };

	private:
		float m_Fps{ 0 };
	};
}

