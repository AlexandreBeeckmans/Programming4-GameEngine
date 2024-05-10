#include "SceneManager.h"
#include "Scene.h"
#include "../Qbert/QbertScenes.h"

void dae::SceneManager::Update()
{
	if(m_pSceneCollection)
		m_pSceneCollection->Update();
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void dae::SceneManager::Init()
{
	for (auto& scene : m_scenes)
	{
		scene->Init();
	}
}

void dae::SceneManager::RemoveAllDeadComponents()
{
	for (auto& scene : m_scenes)
	{
		scene->RemoveAllDeadComponent();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderGui() const
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderGui();
	}
}

void dae::SceneManager::ClearScenes()
{
	m_scenes.clear();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
