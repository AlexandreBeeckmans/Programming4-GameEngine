#pragma once

#include "BaseComponent.h"

namespace dae
{
	class HealthComponent;
}

namespace qbert
{
	class PlayerState;

	class QbertFSMManagerComponent final : public dae::BaseComponent
	{
	public:
		QbertFSMManagerComponent(dae::GameObject* owner);
		virtual ~QbertFSMManagerComponent() override = default;


		QbertFSMManagerComponent(const QbertFSMManagerComponent& other) = delete;
		QbertFSMManagerComponent(QbertFSMManagerComponent&& other) = delete;
		QbertFSMManagerComponent& operator=(const QbertFSMManagerComponent& other) = delete;
		QbertFSMManagerComponent& operator=(QbertFSMManagerComponent&& other) = delete;

		virtual void Init() override;
		virtual void Update() override;

	private:
		PlayerState* m_PlayerState{ nullptr };
	};
}


