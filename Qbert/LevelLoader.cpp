#include "LevelLoader.h"

#include "ResourceManager.h"

qbert::LevelInfo qbert::LevelLoader::LoadLevel(const int level, const int round)
{
	auto jsonLevel = dae::ResourceManager::GetInstance().ReadFile("qbert/Levels/Level_" + std::to_string(level) + "_" + std::to_string(round) + ".json");

	return LevelInfo
	{
		jsonLevel["nbCoily"],
		jsonLevel["nbSlick"],
		jsonLevel["nbUgg"]
	};
}
