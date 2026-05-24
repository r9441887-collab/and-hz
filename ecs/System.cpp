#include "../../include/ecs/System.hpp"

void SystemManager::init(World& world) {
    for (auto& entry : systems_) {
        entry.system->init(world);
    }
}

void SystemManager::update(World& world, float dt) {
    for (auto& entry : systems_) {
        entry.system->update(world, dt);
    }
}

void SystemManager::render(World& world, Renderer& renderer) {
    for (auto& entry : systems_) {
        entry.system->render(world, renderer);
    }
}
