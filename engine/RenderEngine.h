#pragma once

#include <vector>
#include <utility>
#include <SDL.h>

namespace engine {

	class RenderLayer;
	class RenderEngine;

	enum RenderLayers {
		background = -1,
		water,
		tiles,
		entities,
		player,
		front
	};

	class RenderTexture {
	public:
		SDL_Texture* texture;
		SDL_Rect* srcrect;
		SDL_Rect* dstrect;
		double angle;
		SDL_Point* center;
		SDL_RendererFlip flip;

		RenderTexture(SDL_Texture* texture);
		~RenderTexture();

		bool isEx();

	};

	class RenderLayer {
		friend class RenderEngine;
	private:
		int32_t m_layer;
		RenderEngine* m_engine;
		std::vector<RenderTexture> m_textures;
		SDL_Surface* m_surface;
	public:
		RenderLayer(RenderEngine* engine, int32_t layer);
		void add_texture(RenderTexture texture);
		SDL_Surface* get_surface();
		int32_t get_layer() const;
		std::vector<RenderTexture>& get_textures();
	};

	class RenderEngine {
		friend class RenderLayer;
	private:
		uint32_t m_width;
		uint32_t m_height;
		std::vector<RenderLayer*> m_layers;
	public:
		RenderEngine(uint32_t width, uint32_t height);
		~RenderEngine();
		RenderLayer* get_layer(int32_t layer);
		std::vector<RenderLayer*>& get_layers();
	};

}