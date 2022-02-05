#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <mutex>
#include <map>
#include <SDL.h>

#include "App.h"
#include "Vec.h"
#include "RenderEngine.h"

namespace engine {

	enum ComponentTypes {
		transform_ct,
		render_ct,
		last_ct
	};

	class Entity;
	class Component;
	class App;

	constexpr auto LastComponent = last_ct;

	using ComponentType = int32_t;
	using RotationType = int16_t;

	class Component {
	protected:
		const Entity* m_owner;
		const ComponentType m_type;
	public:
		Component(Entity* owner, ComponentType type);
		ComponentType get_type() const;
		virtual void init() {};
		virtual void update(uint64_t delta) {};
		virtual void render(engine::RenderEngine& renderEngine, uint64_t delta) {};
		virtual void stop() {};
	};

	class App {
		friend class Entity;
		friend void __update_thread_func(App*);
	private:
		std::atomic_bool running;
		std::thread* m_update_thread;
		std::vector<Entity*> m_entities;
		std::map<ComponentType, std::vector<Component*>> m_cached_components;
	protected:
		void cache_component(Component* component);
	public:
		App();
		~App();
		void run();
		void stop();
		void add_entity(Entity* entity);
		Entity* new_entity();
	};

	class Entity {
		friend class App;
	private:
		App* app;
		std::vector<Component*> m_components;
		std::mutex m_lock; /* Locking entity to not execute render and update functions in the same time */
		uint64_t m_last_update;
		uint64_t m_last_render;
	public:
		Entity(engine::App* app);
		~Entity();
		void init();
		void update();
		void render(engine::RenderEngine& renderEngine);
		void stop();
		void add_component(Component* component);
		Component* find(ComponentType type) const;
	};

	class Transform : public Component {
	private:
		engine::Vec2f m_position;
		engine::Vec2f m_scale;
		RotationType m_rotation;
	public:
		Transform(Entity* owner);
		engine::Vec2f get_position() const;
		void set_position(engine::Vec2f position);
		engine::Vec2f get_scale() const;
		void set_scale(engine::Vec2f scale);
		RotationType get_rotation() const;
		void set_rotation(RotationType rotation);
	};

	void __update_thread_func(App* app);

}