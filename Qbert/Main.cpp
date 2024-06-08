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

#include"QbertScenes.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameObject.h"


void Load()
{
	qbert::QbertScenes::GetInstance().Init();
	std::unique_ptr<qbert::QbertScenes> sceneCollec{ std::make_unique<qbert::QbertScenes>() };
	dae::SceneManager::GetInstance().SetSceneCollection(std::move(sceneCollec));
	qbert::QbertScenes::GetInstance().LoadSounds();
}

int main(int, char* [])
{



	dae::Minigin engine("../Data/");

	

	

	engine.Run(Load);
	return 0;
}