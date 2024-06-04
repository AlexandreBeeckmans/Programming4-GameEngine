#pragma once
#include <glm/vec3.hpp>


namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}
		virtual void Init() {}

		virtual void Render() const {}
		virtual void RenderGui() const {}

		BaseComponent(GameObject* pGameObject);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		void Destroy() { m_IsDead = true; }
		bool GetIsDead() const { return m_IsDead; }

		glm::vec3 GetWorldPosition() const;

		const GameObject* GetParent() const;
		void SetParent(GameObject* newParent) const;
		void DetachFromParent() const;
		void DetachAllChildren() const;

	protected:
		GameObject* GetOwner() const;

	private:
		GameObject* m_pOwnerObject{};
		bool m_IsDead{ false };

	};
}


