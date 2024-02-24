#pragma once

#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class FPSComponent final: public BaseComponent
	{

	public:

		FPSComponent(GameObject* pGameObject);
		~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = default;
		FPSComponent(FPSComponent&& other) = default;
		FPSComponent& operator=(const FPSComponent& other) = default;
		FPSComponent& operator=(FPSComponent&& other) = default;


		void Update() override;
		float GetFPS() { return m_Fps; };

	private:
		float m_Fps{ 0 };
	};
}

