#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"

#include <iostream>
#include <fstream>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	auto textureToReturn = std::make_unique<Texture2D>(texture);
	return std::move(textureToReturn);

}

std::unique_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	auto fontToReturn = std::make_unique<Font>(m_dataPath + file, size);
	return std::move(fontToReturn);
}

nlohmann::json dae::ResourceManager::ReadFile(const std::string& path) const
{
	std::ifstream inputFile(m_dataPath + path);
	if (!inputFile.is_open())
	{
		std::string errorMessage{ "Failed to open " + path };
		std::cerr << errorMessage << "\n";
		return {};
	}

	nlohmann::json doc{};
	try
	{
		doc = nlohmann::json::parse(inputFile);
		return doc;
	}
	catch (const nlohmann::json::parse_error& e)
	{
		const std::string errorMessage{ "JSON parsing error: " + std::string{ e.what() } };
		std::cerr << errorMessage << '\n';
	}


	return {};
}
