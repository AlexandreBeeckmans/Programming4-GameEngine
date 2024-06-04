#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace qbert
{
	class QbertMoveComponent;
}

namespace qbert
{
	class MapComponent;
}

namespace qbert
{
	class DiscComponent final : public dae::BaseComponent
	{
	public:
		DiscComponent(dae::GameObject* pGameObject, MapComponent* pMap, const bool isLeft = true);
		virtual ~DiscComponent() override = default;


		DiscComponent(const DiscComponent& other) = delete;
		DiscComponent(DiscComponent&& other) = delete;
		DiscComponent& operator=(const DiscComponent& other) = delete;
		DiscComponent& operator=(DiscComponent&& other) = delete;

		virtual void Update() override;

		void SetTarget(const glm::vec2& target) { m_Target = target; }
		void SetActive(const bool isActive, dae::GameObject* qbert);

	private:
		void SetRandomRow();


		int m_Row;
		MapComponent* m_pMap;
		bool m_IsLeft;

		bool m_IsActivated{ false };
		glm::vec2 m_Target{};
	};
	
}


