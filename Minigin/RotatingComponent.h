#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;

	class RotatingComponent final : public BaseComponent
	{
	public:
		RotatingComponent(GameObject* pGameObject, const float speed = 5.0f, const float radius = 15.0f);
		~RotatingComponent() = default;

		RotatingComponent(const RotatingComponent& other) = default;
		RotatingComponent(RotatingComponent&& other) = default;
		RotatingComponent& operator=(const RotatingComponent& other) = default;
		RotatingComponent& operator=(RotatingComponent&& other) = default;

		void Update();

	private:

		const float m_Speed{ 5.0f };
		float m_Angle{ 0.0f };
		glm::vec2 m_Center{ 0,0 };
		float m_Radius{ 15.0f };

	};
}


