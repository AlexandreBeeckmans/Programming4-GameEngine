#pragma once
#include "Observer.h"
#include "Singleton.h"
//Storage class for any type of data that should be saved between scenes
//Singleton interface for the games

namespace dae
{
	class GameState : public Observer
	{
	};
}


