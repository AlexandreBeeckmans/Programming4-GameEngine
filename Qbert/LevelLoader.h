#pragma once
#include "Singleton.h"

namespace qbert
{
	struct LevelInfo
	{
		int nbCoily;
		int nbSlick;
		int nbUgg;
	};

	class LevelLoader final : public dae::Singleton<LevelLoader> 
	{
	public:
		LevelInfo LoadLevel(const int level, const int round);
	};
}


