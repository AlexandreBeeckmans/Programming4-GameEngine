#pragma once
#include "BaseComponent.h"

namespace qbert
{
	class GridMoveComponent;
	class MapComponent;

	class UggDirectionComponent final : public dae::BaseComponent
	{
	public:
		UggDirectionComponent(dae::GameObject* owner, MapComponent* pMap, bool isLeft = true);
		virtual ~UggDirectionComponent() override = default;


		UggDirectionComponent(const UggDirectionComponent& other) = delete;
		UggDirectionComponent(UggDirectionComponent&& other) = delete;
		UggDirectionComponent& operator=(const UggDirectionComponent& other) = delete;
		UggDirectionComponent& operator=(UggDirectionComponent&& other) = delete;

		virtual void Init() override;
		void SetMovementDirection();
		void ResetPosition();

		bool IsLeft()const{ return m_isLeft; }

	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };
		MapComponent* m_pMap{ nullptr };

		bool m_isLeft{ true };
		int m_MovementState{ 0 };

	};
}


