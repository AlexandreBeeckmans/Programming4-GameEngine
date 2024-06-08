#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;
		void RenderGui() const;

		void RemoveAllDeadComponent();

		~Scene() = default;
		void Init();
		Scene(const Scene& other) = default;
		Scene(Scene&& other) = default;
		Scene& operator=(const Scene& other) = default;
		Scene& operator=(Scene&& other) = default;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};
}
