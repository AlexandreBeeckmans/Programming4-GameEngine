#pragma once
#include <vector>
#include <string>
#include <memory>

#include "SceneCollection.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetSceneCollection(std::unique_ptr<SceneCollection> collec) { m_pSceneCollection = std::move(collec); }

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Init();

		void RemoveAllDeadComponents();

		void Render() const;
		void RenderGui() const;

		void ClearScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		std::unique_ptr<SceneCollection> m_pSceneCollection;
	};
}
