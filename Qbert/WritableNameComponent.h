#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
}

namespace qbert
{
	class WritableNameComponent final : public dae::BaseComponent
	{
	public:
		WritableNameComponent(dae::GameObject* pOwner);
		virtual ~WritableNameComponent() override = default;

		WritableNameComponent(const WritableNameComponent& other) = delete;
		WritableNameComponent(WritableNameComponent&& other) = delete;
		WritableNameComponent& operator=(const WritableNameComponent& other) = delete;
		WritableNameComponent& operator=(WritableNameComponent&& other) = delete;

		virtual void Init() override;

		void IncrementCurrentLetter();
		void IncrementLetterIndex();

	private:
		dae::TextComponent* m_pTextComponent{ nullptr };

		int m_CurrentWriteIndex{};
	};
}


