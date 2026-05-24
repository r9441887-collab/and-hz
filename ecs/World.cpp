#include "../../include/ecs/World.hpp"
#include "../../include/ecs/Component.hpp"

World::World() = default;

World::~World() = default;

Entity World::createEntity() {
    return entityManager_.createEntity();
}

void World::destroyEntity(Entity entity) {
    for (auto& [key, storage] : storages_) {
        (void)key;
        auto* base = storage.get();
        (void)base;
    }
    entityManager_.destroyEntity(entity);
}

bool World::isValid(Entity entity) const {
    return entityManager_.isValid(entity);
}
