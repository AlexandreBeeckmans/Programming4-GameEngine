#pragma once
#include "Level.h"

namespace qbert
{
	class MainLevel : public dae::Level
	{
	public:
		MainLevel(const int levelNb, const int roundNb, const int nbPlayer, const bool isVersus );
		virtual void Load() override;
		virtual ~MainLevel() override = default;
	private:
		int m_LevelNb;
		int m_RoundNb;
		int m_NbPlayer;
		bool m_IsVersus;
	};
}


