#pragma once
#include <memory>
#include "Transform.h"

#include<vector>
#include<algorithm>

#include "BaseComponent.h"
#include <string>

#include<glm/glm.hpp>

#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;
		void RenderGui() const;

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalPosition(const glm::vec3& pos);
		void Init();

		GameObject() = default;
		GameObject(std::unique_ptr<Observer> pObserver);

		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void RemoveAllDeadComponent();

		template<typename TComponent, typename ...Args>
		void AddComponent(Args&&... args)
		{
			m_pComponents.push_back(std::make_unique<TComponent>(this, args...));
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
			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](const std::unique_ptr<dae::BaseComponent>& component)
																							{
																								return dynamic_cast<TComponent*>(component.get());
																							});

			return (find != std::cend(m_pComponents));
		}

		template<typename TComponent>
		TComponent* GetComponent()
		{
			if (!HasComponent<TComponent>()) return nullptr;



			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](const std::unique_ptr<BaseComponent>& component)
				{
					return dynamic_cast<TComponent*>(component.get());
				}); 

			return dynamic_cast<TComponent*>(find->get());
		}

		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, const bool keepWorldPosition = false);
		void DetachFromParent();


		//Position
		glm::vec3 GetLocalPosition() const;
		glm::vec3 GetWorldPosition();
		void Translate(const glm::vec2& discplacement);

		//Event
		void Notify(const Event& event);

		Subject* GetDieEvent() { return m_pEventSubject.get(); };

	private:
		Transform m_transform{};
		std::vector<std::unique_ptr<BaseComponent>>m_pComponents{};



		//Scenegraph
		GameObject* m_pParent{nullptr};
		std::vector<GameObject*> m_pChildren{};

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		bool IsChild(GameObject* pParent) const;

		void UpdateWorldPosition();
		void SetPositionDirty();

		bool m_IsPositionDirty{ false };
		glm::vec3 m_WorldPosition{};



		//Events
		std::unique_ptr<Subject> m_pEventSubject;
	};
}
