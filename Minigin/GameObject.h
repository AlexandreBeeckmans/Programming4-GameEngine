#pragma once
#include <memory>
#include "Transform.h"

#include<vector>
#include<algorithm>

#include "BaseComponent.h"
#include <string>

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

		auto GetPosition() const { return m_transform.GetPosition(); };

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename TComponent, typename ...Args>
		void AddComponent(Args&&... args)
		{
			m_pComponents.push_back(std::make_shared<TComponent>(args...));
		}

		template<typename TComponent>
		void RemoveComponent()
		{
			std::erase_if(m_pComponents, [](std::shared_ptr<dae::BaseComponent>& component) 
											{ 
												return dynamic_cast<TComponent*>(component.get());
											});
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



	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<BaseComponent>>m_pComponents{};
	};
}
