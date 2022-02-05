#include "App.h"
#include <time.h>

inline uint64_t time() {
	return std::time(NULL);
}

engine::App::App() : running(true), m_update_thread(nullptr) {}

engine::App::~App()
{
	for (Entity* entity : m_entities) {
		delete entity;
	}
	if (m_update_thread != nullptr) {
		delete m_update_thread;
	}
}

void engine::App::cache_component(engine::Component* component)
{
	if (m_cached_components.contains(component->get_type())) {
		m_cached_components[component->get_type()].push_back(component);
	}
	m_cached_components[component->get_type()] = std::vector<engine::Component*>(1, component);
}

void engine::App::add_entity(engine::Entity* entity)
{
	m_entities.push_back(entity);
}

engine::Entity* engine::App::new_entity()
{
	engine::Entity* result = new engine::Entity(this);
	add_entity(result);
	return result;
}

engine::Component::Component(Entity* owner, engine::ComponentType type)
	: m_owner(owner), m_type(type) {}

engine::ComponentType engine::Component::get_type() const
{
	return m_type;
}

engine::Entity::Entity(engine::App* app) 
	: app(app), m_last_render(-1), m_last_update(-1) {}

engine::Entity::~Entity() {
	for (Component* comp : m_components) {
		delete comp;
	}
}

void engine::Entity::init()
{
	m_lock.lock();
	for (Component* comp : m_components) {
		comp->init();
	}
	m_last_render = time();
	m_last_update = time();
	m_lock.unlock();
}

void engine::Entity::update()
{
	m_lock.lock();
	for (Component* comp : m_components) {
		comp->update(time() - m_last_update);
	}
	m_last_update = time();
	m_lock.unlock();
}

void engine::Entity::add_component(Component* component)
{
	m_components.push_back(component);
	app->cache_component(component);
}

engine::Component* engine::Entity::find(ComponentType type) const
{
	for (Component* comp : m_components) {
		if (comp->get_type() == type) {
			return comp;
		}
	}
	return nullptr;
}

void engine::Entity::render(engine::RenderEngine& renderEngine)
{
	m_lock.lock();
	for (Component* comp : m_components) {
		comp->render(renderEngine, time() - m_last_render);
	}
	m_last_render = time();
	m_lock.unlock();
}

void engine::Entity::stop()
{
	m_lock.lock();
	for (Component* comp : m_components) {
		comp->stop();
	}
	m_lock.unlock();
}

engine::Transform::Transform(Entity* owner): 
	Component::Component(owner, engine::transform_ct),
	m_rotation(engine::RotationType(0)) {}

engine::Vec2f engine::Transform::get_position() const
{
	return m_position;
}

void engine::Transform::set_position(engine::Vec2f position)
{
	m_position = position;
}

engine::Vec2f engine::Transform::get_scale() const
{
	return m_scale;
}

void engine::Transform::set_scale(engine::Vec2f scale) {
	m_scale = scale;
}

engine::RotationType engine::Transform::get_rotation() const
{
	return m_rotation;
}

void engine::Transform::set_rotation(engine::RotationType rotation) {
	m_rotation = rotation;
}