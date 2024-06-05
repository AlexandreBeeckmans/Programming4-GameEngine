#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

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
	dae::ServiceLocator::GetSoundSystem().LoadSound("../Data/qbert/Sounds/QBert Jump.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound("../Data/qbert/Sounds/QBert Fall.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound("../Data/qbert/Sounds/Round_Complete_Tune.wav");
	dae::ServiceLocator::GetSoundSystem().LoadSound("../Data/qbert/Sounds/Level Screen Tune.wav");
}

void Load()
{

	LoadSounds();
}




int main(int, char* [])
{

	dae::Minigin engine("../Data/");

	qbert::QbertScenes::GetInstance().Init();

	std::unique_ptr<qbert::QbertScenes> sceneCollec{ std::make_unique<qbert::QbertScenes>() };
	dae::SceneManager::GetInstance().SetSceneCollection(std::move(sceneCollec));

	engine.Run(Load);
	return 0;
}