#pragma once
#include <memory>

#include "NullSoundSystem.h"
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
		

	public:
	
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem);
		
		//static void Init();

	private:
		static std::unique_ptr<SoundSystem> m_Instance;
		static std::unique_ptr<NullSoundSystem>m_NullSystem;
	};

}
