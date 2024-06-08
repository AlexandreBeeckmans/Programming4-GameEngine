#include "LevelLoader.h"

#include "ResourceManager.h"

qbert::LevelInfo qbert::LevelLoader::LoadLevel(const int level, const int round)
{
	auto jsonLevel = dae::ResourceManager::GetInstance().ReadFile("qbert/Levels/Level" + std::to_string(level) + ".json");
	auto obj = jsonLevel[round - 1];
	return LevelInfo
	{
		obj["nbCoily"],
		obj["nbSlick"],
		obj["nbUgg"]
	};
}
