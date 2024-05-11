#pragma once


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

	protected:
		GameObject* GetOwner() const;

	private:
		GameObject* m_pOwnerObject{};
		bool m_IsDead{ false };

	};
}


