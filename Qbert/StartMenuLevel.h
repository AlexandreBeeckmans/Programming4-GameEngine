#pragma once
#include "Level.h"

namespace qbert
{
	class StartMenuLevel final : public dae::Level
	{
	public:
		StartMenuLevel();
		virtual void Load() override;
		virtual ~StartMenuLevel() override = default;
	};
}


