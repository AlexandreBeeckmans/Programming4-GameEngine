#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;

	class RotatingComponent final : public BaseComponent
	{
	public:
		RotatingComponent(GameObject* pGameObject);
		~RotatingComponent() = default;

		RotatingComponent(const RotatingComponent& other) = default;
		RotatingComponent(RotatingComponent&& other) = default;
		RotatingComponent& operator=(const RotatingComponent& other) = default;
		RotatingComponent& operator=(RotatingComponent&& other) = default;

		void Update();

	private:

		const float m_Speed{ 5.0f };
		float m_Angle{ 0.0f };

		float m_CenterX{0.0f};
		float m_CenterY{0.0f};

		float m_Radius{ 15.0f };

	};
}


