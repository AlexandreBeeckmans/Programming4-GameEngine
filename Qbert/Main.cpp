#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <iostream>

#include "EventManager.h"
#include "Minigin.h"
#include "InputManager.h"

#include "GuiEx2Component.h"
#include "ServiceLocator.h"

#include"QbertScenes.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "SoundTypes.h"


void LoadSounds()
{
	std::string path{ dae::ResourceManager::GetInstance().GetPath() + "qbert/Sounds/" };
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Jump.wav", static_cast<int>(qbert::SoundType::JUMP));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Fall.wav", static_cast<int>(qbert::SoundType::FALL));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Round_Complete_Tune.wav", static_cast<int>(qbert::SoundType::WIN));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Level Screen Tune.wav", static_cast<int>(qbert::SoundType::LOAD));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "QBert Hit.wav", static_cast<int>(qbert::SoundType::HIT));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Change Selection.wav", static_cast<int>(qbert::SoundType::MENUSELECTION));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Coily Snake Jump.wav", static_cast<int>(qbert::SoundType::COILYJUMP));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Coily Fall.wav", static_cast<int>(qbert::SoundType::COILYFALL));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Disk Lift.wav", static_cast<int>(qbert::SoundType::DISKMOVE));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Disk Land.wav", static_cast<int>(qbert::SoundType::DISKLAND));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "SlickSam Caught.wav", static_cast<int>(qbert::SoundType::SLICKCAUGHT));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(path + "Swearing.wav", static_cast<int>(qbert::SoundType::SWEAR));
}

void Load()
{

	LoadSounds();
}

void PrintNumber(int number)
{
	std::cout << number;
}


int main(int, char* [])
{
	//dae::EventManager::GetInstance().AddFunction<int>(0, &PrintNumber, 5);
	//dae::EventManager::GetInstance().CallFunction(0);


	dae::Minigin engine("../Data/");

	qbert::QbertScenes::GetInstance().Init();

	std::unique_ptr<qbert::QbertScenes> sceneCollec{ std::make_unique<qbert::QbertScenes>() };
	dae::SceneManager::GetInstance().SetSceneCollection(std::move(sceneCollec));

	engine.Run(Load);
	return 0;
}