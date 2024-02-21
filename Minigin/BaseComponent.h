#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void Update(const float deltaTime) = 0;
		virtual void Render()
		{

		}

		BaseComponent(GameObject* m_pParent);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = default;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		dae::GameObject* m_pParent{};
	};
}


