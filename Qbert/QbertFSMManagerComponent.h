#pragma once

#include <memory>

#include "BaseComponent.h"
#include "PlayerState.h"

namespace dae
{
	class HealthComponent;
}

namespace qbert
{
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
		std::unique_ptr<PlayerState> m_PlayerState{ nullptr };
	};
}


