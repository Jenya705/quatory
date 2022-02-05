#include "App.h"
#include <iostream>
#include <algorithm>

#define WIDTH 640
#define HEIGHT 480

bool __render_layer_compare(const engine::RenderLayer* layer1, const engine::RenderLayer* layer2) {
	return layer1->get_layer() < layer2->get_layer();
}

void __render_texture(SDL_Renderer* ren, engine::RenderTexture& texture) {
	if (texture.isEx()) {
		SDL_RenderCopyEx(
			ren,
			texture.texture,
			texture.srcrect,
			texture.dstrect,
			texture.angle,
			texture.center,
			texture.flip
		);
	}
	else {
		SDL_RenderCopy(
			ren,
			texture.texture,
			texture.srcrect,
			texture.dstrect
		);
	}
}

void engine::App::run()
{
	running.store(true);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		std::exit(1);
	}
	SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		std::exit(1);
	}
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		std::exit(1);
	}
	m_update_thread = new std::thread(engine::__update_thread_func, this);
	while (running.load()) {
		engine::RenderEngine renderEngine(WIDTH, HEIGHT);
		for (auto it = m_entities.rbegin(); it != m_entities.rend(); it++) {
			(*it)->render(renderEngine);
		}
		auto layers = renderEngine.get_layers();
		std::sort(layers.begin(), layers.end(), __render_layer_compare);
		SDL_RenderClear(ren);
		for (RenderLayer* layer : layers) {
			for (RenderTexture& texture : layer->get_textures()) {
				__render_texture(ren, texture);
			}
			auto surface = layer->get_surface();
			if (surface != nullptr) {
				auto surface_texture = SDL_CreateTextureFromSurface(ren, surface);
				SDL_FreeSurface(surface);
				SDL_RenderCopy(ren, surface_texture, nullptr, nullptr);
				SDL_DestroyTexture(surface_texture);
			}
		}
		SDL_RenderPresent(ren);
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	m_update_thread->join();
}

void engine::App::stop()
{
	running.store(false);
}

void engine::__update_thread_func(App* app) {
	while (app->running.load()) {
		for (Entity* entity : app->m_entities) {
			entity->update();
		}
	}
}