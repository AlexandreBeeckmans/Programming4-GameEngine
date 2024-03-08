#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* dae::Font::GetFont() const {
	return m_font;
}

dae::Font::Font(const std::string& fullPath, unsigned int size) : 
	m_font(nullptr),
	m_Path{fullPath},
	m_Size{size}

{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::Font(const Font& font) :
	m_font{ nullptr },
	m_Path{ font.m_Path },
	m_Size{ font.m_Size }

{

	m_font = TTF_OpenFont(m_Path.c_str(), m_Size);
	if (m_font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_font);
}
