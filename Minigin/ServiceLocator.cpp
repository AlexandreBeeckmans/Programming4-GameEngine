#include "ServiceLocator.h"
#include <iostream>

#include "NullSoundSystem.h"

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	if(!m_IsMuted)
		return *m_Instance;

	return *m_NullSystem;
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

void dae::ServiceLocator::Update()
{
	m_Instance->Update();
}

void dae::ServiceLocator::Mute()
{
	m_IsMuted = !m_IsMuted;

	if (m_IsMuted)
		m_Instance->StopAll();
}
