#include "RenderEngine.h"

engine::RenderTexture::RenderTexture(SDL_Texture* texture) : 
	texture(texture),
	srcrect(nullptr),
	dstrect(nullptr),
	angle(0),
	center(nullptr),
	flip(SDL_FLIP_NONE) {}

engine::RenderTexture::~RenderTexture() {
	if (srcrect != nullptr) {
		delete srcrect;
	}
	if (dstrect != nullptr) {
		delete dstrect;
	}
	if (center != nullptr) {
		delete center;
	}
}

bool engine::RenderTexture::isEx() {
	return angle == 0 && 
		center == nullptr && 
		flip == SDL_FLIP_NONE;
}

engine::RenderLayer::RenderLayer(engine::RenderEngine* engine, int32_t layer)
	: m_engine(engine), m_surface(nullptr), m_layer(layer) {}

void engine::RenderLayer::add_texture(RenderTexture texture) {
	m_textures.push_back(texture);
}

SDL_Surface* engine::RenderLayer::get_surface() {
	if (m_surface == nullptr) {
		m_surface = SDL_CreateRGBSurface(
			0, m_engine->m_width, m_engine->m_height, 32, 0, 0, 0, 0);
	}
	return m_surface;
}

int32_t engine::RenderLayer::get_layer() const {
	return m_layer;
}

std::vector<engine::RenderTexture>& engine::RenderLayer::get_textures() {
	return m_textures;
}

engine::RenderEngine::RenderEngine(uint32_t width, uint32_t height) 
	: m_width(width), m_height(height) {}

engine::RenderLayer* engine::RenderEngine::get_layer(int32_t layer) {
	for (RenderLayer* renderLayer : m_layers) {
		if (renderLayer->m_layer == layer) {
			return renderLayer;
		}
	}
	auto* renderLayer = new engine::RenderLayer(this, layer);
	m_layers.push_back(renderLayer);
	return renderLayer;
}

std::vector<engine::RenderLayer*>& engine::RenderEngine::get_layers() {
	return m_layers;
}

engine::RenderEngine::~RenderEngine()
{
	for (RenderLayer* renderLayer : m_layers) {
		delete renderLayer;
	}
}
