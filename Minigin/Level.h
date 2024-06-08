#pragma once
#include "Scene.h"

namespace dae
{
	class Level
	{
	public:
		virtual void Load() = 0;
		virtual ~Level() = default;
	};
}


