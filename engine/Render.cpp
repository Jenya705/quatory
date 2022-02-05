#include "Render.h"

engine::RenderComponent::RenderComponent(engine::Entity* owner) :
	engine::Component::Component(owner, render_ct),
	m_layer(tiles),
	m_type(RenderType::rect),
	m_color(engine::RGB(0)),
	m_texture(nullptr) {}

void engine::RenderComponent::render(engine::RenderEngine& engine, uint64_t delta)
{
	switch (m_type) {
	case RenderType::rect:
		__rect_render(*this, engine);
		break;
	}
}

void engine::RenderComponent::set_layer(uint32_t layer) {
	m_layer = layer;
}

uint32_t engine::RenderComponent::get_layer() {
	return m_layer;
}

void engine::RenderComponent::set_color(engine::Color color) {
	m_color = color;
}

engine::Color engine::RenderComponent::get_color() {
	return m_color;
}

void engine::RenderComponent::set_type(RenderType type) {
	m_type = type;
}

engine::RenderType engine::RenderComponent::get_type()
{
	return m_type;
}

void engine::RenderComponent::set_texture(SDL_Texture* texture) {
	m_texture = texture;
}

SDL_Texture* engine::RenderComponent::get_texture()
{
	return m_texture;
}

#include <iostream>

void engine::__rect_render(engine::RenderComponent& renderComponent, engine::RenderEngine& engine) {
	auto* transform = static_cast<engine::Transform*>(renderComponent.m_owner->find(transform_ct));
	if (transform == nullptr) return;
	auto position = transform->get_position().cast<int>();
	auto scale = transform->get_scale().cast<int>();
	auto layer = engine.get_layer(renderComponent.m_layer);
	auto surface = layer->get_surface();
	auto rect = new SDL_Rect{ position.x, position.y, scale.x, scale.y };
	auto texture = renderComponent.m_texture;
	if (texture == nullptr) {
		SDL_FillRect(surface, rect, renderComponent.m_color.sdl(surface->format));
		delete rect;
	}
	else { 
		auto rotation = transform->get_rotation();
		engine::RenderTexture renderTexture(texture);
		renderTexture.dstrect = rect;
		renderTexture.angle = rotation;
		layer->add_texture(renderTexture);
	}
}