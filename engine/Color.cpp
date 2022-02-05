#include "Color.h"

engine::Color::Color(uint8_t r, uint8_t g, uint8_t b) 
	: engine::Color::Color(r, g, b, engine::max_color) {}

engine::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
	: r(r), g(g), b(b), a(a) {}


uint32_t engine::Color::sdl(SDL_PixelFormat* format) {
	return SDL_MapRGBA(format, r, g, b, a);
}

engine::Color engine::RGB(uint8_t r, uint8_t g, uint8_t b)
{
	return RGBA(r, g, b, engine::max_color);
}

engine::Color engine::RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return engine::Color(r, g, b, a);
}

engine::Color engine::RGB(uint32_t color) {
	return engine::Color(
		static_cast<uint8_t>((color & engine::r_mask) >> 16),
		static_cast<uint8_t>((color & engine::g_mask) >> 8),
		static_cast<uint8_t>(color & engine::b_mask)
	);
}

engine::Color engine::RGBA(uint32_t color) {
	return engine::Color(
		static_cast<uint8_t>((color & engine::r_mask) >> 24),
		static_cast<uint8_t>((color & engine::g_mask) >> 16),
		static_cast<uint8_t>((color & engine::b_mask) >> 8),
		static_cast<uint8_t>(color & engine::a_mask)
	);
}