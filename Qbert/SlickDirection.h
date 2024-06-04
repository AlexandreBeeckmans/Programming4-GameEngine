#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;
	class MapComponent;

	class SlickDirection final : public dae::BaseComponent
	{
	public:
		SlickDirection(dae::GameObject* owner, MapComponent* pMap);
		virtual ~SlickDirection() override = default;


		SlickDirection(const SlickDirection& other) = delete;
		SlickDirection(SlickDirection&& other) = delete;
		SlickDirection& operator=(const SlickDirection& other) = delete;
		SlickDirection& operator=(SlickDirection&& other) = delete;

		virtual void Init() override;
		void SetMovementDirection() const;
		void ResetPosition() const;
		
	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };
		MapComponent* m_pMap{ nullptr };
	};
}


