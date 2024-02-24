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
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);

		auto GetPosition() const { return m_transform.GetPosition(); };

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename TComponent>
		void AddComponent(TComponent componentToAdd)
		{
			m_pComponents.push_back(std::make_shared<TComponent>(componentToAdd));
		}

		template<typename TComponent>
		void AddComponent()
		{
			m_pComponents.push_back(std::make_shared<TComponent>());
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
		bool HasComponent()
		{
			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](std::shared_ptr<dae::BaseComponent>& component)
																							{
																								return dynamic_cast<TComponent*>(component.get());
																							});

			return (find != std::cend(m_pComponents));
		}

		template<typename TComponent>
		BaseComponent* GetComponent()
		{
			if (!HasComponent<TComponent>()) return nullptr;

			auto find = std::find_if(std::cbegin(m_pComponents), std::cend(m_pComponents), [](std::shared_ptr<dae::BaseComponent>& component)
				{
					return dynamic_cast<TComponent*>(component.get());
				});
			return *find;
		}



	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<BaseComponent>>m_pComponents{};
	};
}
