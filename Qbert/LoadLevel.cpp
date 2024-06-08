#include "LoadLevel.h"

#include "Minigin.h"
#include "ServiceLocator.h"
#include "SoundTypes.h"

qbert::LoadLevel::LoadLevel(const int levelNb) :
m_LevelNb(levelNb)
{
}

void qbert::LoadLevel::Load()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("test");

	auto loadObject = std::make_unique<dae::GameObject>();
	loadObject->AddComponent<dae::ImageComponent>("qbert/Level_" + std::to_string(m_LevelNb + 1) + "_Title.png");

	loadObject->GetComponent<dae::ImageComponent>()->SetWidth(dae::Minigin::GetWindowWidth());
	loadObject->GetComponent<dae::ImageComponent>()->SetHeight(dae::Minigin::GetWindowHeight());

	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<int>(SoundType::LOAD), 100.0f);



	scene.Add(std::move(loadObject));
}
