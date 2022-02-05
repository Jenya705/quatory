#include <iostream>
#include <SDL.h>
#include "engine/App.h"
#include "engine/Render.h"

int main(int argc, char** argv) {
    engine::App app;
    auto* entity = app.new_entity(); 
    auto* transform = new engine::Transform(entity);
    transform->set_scale(engine::Vec2f(50, 50));
    transform->set_position(engine::Vec2f(50, 50));
    entity->add_component(transform);
    auto* render = new engine::RenderComponent(entity);
    render->set_color(engine::RGBA(255, 0, 0, 0));
    entity->add_component(render);
    app.run();
    return 0;
}
