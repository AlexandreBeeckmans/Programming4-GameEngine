#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const
		{

		}

		BaseComponent(GameObject* m_pParent);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = default;
		BaseComponent(BaseComponent&& other) = default;
		BaseComponent& operator=(const BaseComponent& other) = default;
		BaseComponent& operator=(BaseComponent&& other) = default;

	protected:
		dae::GameObject* m_pParent{};
	};
}


