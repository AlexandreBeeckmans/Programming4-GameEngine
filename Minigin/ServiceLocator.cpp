#include "ServiceLocator.h"
#include <iostream>

#include "NullSoundSystem.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_Instance{ std::make_unique<NullSoundSystem>() };

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_Instance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
{
	if(soundSystem == nullptr)
	{
		m_Instance = std::make_unique<NullSoundSystem>();
	}
	else
	{
		m_Instance = std::move(soundSystem);
	}
		
}

//void dae::ServiceLocator::Init()
//{
//	std::cout << "SDL Mixer initializing...\n";
//	m_Instance->Init();
//	std::cout << "SDL Mixer initialized...\n";
//}
