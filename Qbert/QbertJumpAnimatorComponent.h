#pragma once
#include "GameObject.h"

namespace qbert
{
	class GridMoveComponent;

	class QbertJumpAnimatorComponent final : public dae::BaseComponent
	{
	public:
		QbertJumpAnimatorComponent(dae::GameObject* owner);
		virtual ~QbertJumpAnimatorComponent() override = default;


		QbertJumpAnimatorComponent(const QbertJumpAnimatorComponent& other) = delete;
		QbertJumpAnimatorComponent(QbertJumpAnimatorComponent&& other) = delete;
		QbertJumpAnimatorComponent& operator=(const QbertJumpAnimatorComponent& other) = delete;
		QbertJumpAnimatorComponent& operator=(QbertJumpAnimatorComponent&& other) = delete;

		virtual void Init() override;

		void SetJumpSprite() const;

	private:
		GridMoveComponent* m_pMoveComponent{ nullptr };
	};
}


