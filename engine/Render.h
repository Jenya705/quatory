#pragma once

#include "App.h"
#include "Color.h"

namespace engine {

	enum class RenderType {
		rect
	};

	class RenderComponent : public engine::Component {
		friend void __rect_render(RenderComponent&, engine::RenderEngine&);
	private:
		uint32_t m_layer;
		engine::Color m_color;
		RenderType m_type;
		SDL_Texture* m_texture;
	public:
		RenderComponent(engine::Entity* owner);
		void render(engine::RenderEngine& engine, uint64_t delta);
		void set_layer(uint32_t layer);
		uint32_t get_layer();
		void set_color(engine::Color color);
		engine::Color get_color();
		void set_type(RenderType type);
		RenderType get_type();
		void set_texture(SDL_Texture* texture);
		SDL_Texture* get_texture();
	};

	void __rect_render(RenderComponent& renderComponent, engine::RenderEngine& engine);

}