#include "ServiceLocator.h"
#include <iostream>

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_Instance{ nullptr };

void dae::ServiceLocator::Init()
{
	std::cout << "SDL Mixer initializing..." << std::endl;
	m_Instance->Init();
	std::cout << "SDL Mixer initialized..." << std::endl;
}
