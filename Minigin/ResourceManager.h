#pragma once
#include <string>
#include <memory>
#include "Singleton.h"

#include "Texture2D.h"
#include "Font.h"
#include<json.hpp>

namespace dae
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::unique_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::unique_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		nlohmann::json ReadFile(const std::string& path) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
