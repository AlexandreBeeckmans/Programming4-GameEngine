#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	private:
		static std::unique_ptr<SoundSystem> m_Instance;

	public:
	
		static SoundSystem& GetSoundSystem() { return *m_Instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
		{
			m_Instance = std::move(soundSystem);
		}
		static void Init();
	};

}
