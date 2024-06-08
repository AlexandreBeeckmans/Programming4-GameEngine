#pragma once
#include "Level.h"

namespace qbert
{
	class GameOverLevel final : public dae::Level
	{
	public:
		GameOverLevel();
		virtual void Load() override;
		virtual ~GameOverLevel() override = default;
	};
}


