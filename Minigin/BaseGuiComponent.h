#pragma once
#include <string>

#include "BaseComponent.h"

namespace dae
{
	class BaseGuiComponent : public BaseComponent
	{
	public:

		BaseGuiComponent(dae::GameObject* pParent, const std::string& name);

		BaseGuiComponent(const BaseGuiComponent& other) = delete;
		BaseGuiComponent(BaseGuiComponent&& other) = delete;
		BaseGuiComponent& operator=(const BaseGuiComponent& other) = delete;
		BaseGuiComponent& operator=(BaseGuiComponent&& other) = delete;

		virtual void RenderGui() const override;


	protected:
		const char* GetName() const { return m_Name.c_str(); };


	private:
		const std::string m_Name;

	};
}


