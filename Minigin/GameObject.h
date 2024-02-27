#pragma once
#include <memory>
#include "Transform.h"

#include<vector>
#include<algorithm>

#include "BaseComponent.h"
#include <string>

#include<glm/glm.hpp>

namespace dae
{
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void RemoveAllDeadComponent();

		template<typename TComponent, typename ...Args>
		void AddComponent(Args&&... args)
		{
			m_pComponents.push_back(std::make_shared<TComponent>(this, args...));
		}

		template<typename TComponent>
		void RemoveComponent()
		{
			for (auto& component : m_pComponents)
			{
				if (dynamic_cast<TComponent*>(component.get()))
					component->Kill();
			}
		}

		template<typename TComponent>
		bool HasComponent() const
		{
			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](const std::shared_ptr<dae::BaseComponent>& component)
																							{
																								return dynamic_cast<TComponent*>(component.get());
																							});

			return (find != std::cend(m_pComponents));
		}

		template<typename TComponent>
		TComponent* GetComponent()
		{
			if (!HasComponent<TComponent>()) return nullptr;



			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](const std::shared_ptr<BaseComponent>& component)
				{
					return dynamic_cast<TComponent*>(component.get());
				}); 

			return dynamic_cast<TComponent*>(find->get());
		}

		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, const bool keepWorldPosition);
		//int GetChildrenCount() const;
		//GameObject* GetChildAt(const int index) const;


		//Position
		glm::vec3 GetLocalPosition() const;
		glm::vec3 GetWorldPosition();


	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<BaseComponent>>m_pComponents{};



		//Scenegraph
		GameObject* m_pParent{nullptr};
		std::vector<GameObject*> m_pChildren{};

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);


		void SetLocalPosition(const glm::vec3& pos);
		void UpdateWorldPosition();
		void SetPositionDirty();

		bool m_IsPositionDirty{ false };
		glm::vec3 m_WorldPosition{};
	};
}
