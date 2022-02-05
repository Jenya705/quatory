#pragma once

#include <cstdint>
#include <SDL.h>

namespace engine {

	constexpr uint8_t max_color = 255;

	constexpr uint32_t r_mask = 0xff000000;
	constexpr uint32_t g_mask = 0x00ff0000;
	constexpr uint32_t b_mask = 0x0000ff00;
	constexpr uint32_t a_mask = 0x000000ff;

	class Color {
	public:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color(uint8_t r, uint8_t g, uint8_t b);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		uint32_t sdl(SDL_PixelFormat* format);
	
	};

	Color RGB(uint8_t r, uint8_t g, uint8_t b);

	Color RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	Color RGB(uint32_t color);

	Color RGBA(uint32_t color);

}