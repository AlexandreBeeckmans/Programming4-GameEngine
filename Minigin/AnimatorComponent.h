#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ImageComponent;
}

namespace dae
{
	class AnimatorComponent final : public BaseComponent
	{
	public:
		AnimatorComponent(GameObject* pGameObject, const bool isActive = true, const float frameTime = 0.5f, const int nbCols = 1, const int nbRows = 1, const int startCol = 0, const int startRow = 0);
		virtual ~AnimatorComponent() override = default;


		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void virtual Update() override;
		void SetActive(const bool isActive);

	private:
		const int m_NbCols;
		const int m_NbRows;

		const float m_FrameTime;

		int m_StartCol;
		int m_StartRow;

		int m_CurrentCol;
		int m_CurrentRow;
		float m_AccumulatedTime;

		ImageComponent* m_pImage;

		bool m_IsActive;

	};
	
}


