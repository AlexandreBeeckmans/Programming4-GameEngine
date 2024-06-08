#pragma once
#include "Level.h"

namespace qbert
{
	class LoadLevel final : public dae::Level
	{
	public:
		LoadLevel(const int levelNb);
		virtual void Load() override;
		virtual ~LoadLevel() override = default;

	private:
		const int m_LevelNb{};
	};
}


