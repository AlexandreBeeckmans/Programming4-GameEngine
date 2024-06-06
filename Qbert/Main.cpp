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


void LoadSounds()
{
	std::string path{ dae::ResourceManager::GetInstance().GetPath() + "qbert/Sounds/" };
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "QBert Jump.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "QBert Fall.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Round_Complete_Tune.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Level Screen Tune.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "QBert Hit.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Change Selection.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Coily Snake Jump.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Coily Fall.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Disk Lift.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Disk Land.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "SlickSam Caught.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound(path + "Swearing.wav");
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