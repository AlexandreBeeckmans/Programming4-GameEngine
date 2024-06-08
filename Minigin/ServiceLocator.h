#pragma once
#include <memory>

#include "NullSoundSystem.h"
#include "Singleton.h"
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:



		SoundSystem& GetSoundSystem();
		void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem);
		void Update();
		void Mute();
		

	private:
		std::unique_ptr<SoundSystem> m_Instance{ std::make_unique<NullSoundSystem>() };
		std::unique_ptr<NullSoundSystem>m_NullSystem{ std::make_unique<NullSoundSystem>() };

		bool m_IsMuted{false};
	};

}
