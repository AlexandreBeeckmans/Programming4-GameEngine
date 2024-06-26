#include "LoggingSoundSystem.h"

#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem):
	m_RealSoundSystem(std::move(soundSystem))
{}

void dae::LoggingSoundSystem::Play(const soundId id, const float volume)
{
	m_RealSoundSystem->Play(id, volume);
	std::cout << "Playing: " << id << " at volume " << volume << "\n";
}

void dae::LoggingSoundSystem::StopAll()
{
	m_RealSoundSystem->StopAll();
	std::cout << "All sounds are stopped";
}

void dae::LoggingSoundSystem::Init()
{
	std::cout << "Init sound system\n";
	m_RealSoundSystem->Init();
}

void dae::LoggingSoundSystem::LoadSound(const std::string& path, const soundId id)
{
	std::cout << "Load sound: " << path <<" \n";
	m_RealSoundSystem->LoadSound(path, id);
}

void dae::LoggingSoundSystem::Update()
{
	m_RealSoundSystem->Update();
}
