#pragma once
#include <memory>
#include "Transform.h"

#include<vector>
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename TComponent>
		void AddComponent()
		{
			m_pComponents.push_back(std::make_unique<TComponent>());
		}

		template<typename TComponent>
		bool HasComponent()
		{
			for (auto& comp : m_pComponents)
			{
				
				if (typeid(*comp.get()) == typeid(TComponent))
				{
					return true;
				}
			}
			return false;
		}

		template<typename TComponent>
		BaseComponent* GetComponent()
		{
			for (auto& comp : m_pComponents)
			{

				if (typeid(*comp.get()) == typeid(TComponent))
				{
					return comp.get();
				}
			}
			return nullptr;
		}



	private:
		Transform m_transform{};

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
		std::vector<std::unique_ptr<BaseComponent>>m_pComponents{};
	};
}
