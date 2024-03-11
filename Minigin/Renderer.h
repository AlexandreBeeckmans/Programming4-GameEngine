#pragma once
#include <SDL.h>
#include "Singleton.h"

#include <memory>

//#include "TrashTheCache.h"


#include "Graph.hpp"

namespace dae
{

	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; };
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; };

	private:

		std::unique_ptr<dae::Graph<int>> m_IntGraph{};
		std::unique_ptr<dae::Graph<TrashGameObject>> m_GOGraph{};
		std::unique_ptr<dae::Graph<TrashGameObjectAlt>> m_GOAltGraph{};

		void DisplayCombinedGraph() const;
	};
}

