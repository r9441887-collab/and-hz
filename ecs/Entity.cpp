#include "../../include/ecs/Entity.hpp"

EntityManager::EntityManager() {
    generations_.fill(0);
}

Entity EntityManager::createEntity() {
    for (size_t i = 1; i < MAX_GEN_ENTITIES; ++i) {
        uint32_t gen = generations_[i];
        if (gen < 256) {
            generations_[i] = gen;
            return createEntityId(static_cast<uint32_t>(i), gen);
        }
    }
    return ENTITY_NULL;
}

void EntityManager::destroyEntity(Entity entity) {
    uint32_t idx = getEntityIndex(entity);
    if (idx == 0 || idx >= MAX_GEN_ENTITIES) return;
    uint32_t gen = getEntityGeneration(entity);
    generations_[idx] = getNextGeneration(gen);
}

bool EntityManager::isValid(Entity entity) const {
    uint32_t idx = getEntityIndex(entity);
    if (idx == 0 || idx >= MAX_GEN_ENTITIES) return false;
    uint32_t gen = getEntityGeneration(entity);
    return generations_[idx] == gen;
}
