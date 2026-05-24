#pragma once
#include <cstdint>
#include <array>

using Entity = uint32_t;

constexpr Entity ENTITY_NULL = 0;
constexpr uint32_t ENTITY_INDEX_MASK = 0x00FFFFFF;
constexpr uint32_t ENTITY_GEN_SHIFT = 24;
constexpr uint32_t MAX_ENTITIES = 0x00FFFFFF;

inline Entity createEntityId(uint32_t index, uint32_t generation) {
    return (index & ENTITY_INDEX_MASK) | (generation << ENTITY_GEN_SHIFT);
}

inline uint32_t getEntityIndex(Entity entity) {
    return entity & ENTITY_INDEX_MASK;
}

inline uint32_t getEntityGeneration(Entity entity) {
    return (entity >> ENTITY_GEN_SHIFT) & 0xFF;
}

inline uint32_t getNextGeneration(uint32_t generation) {
    return (generation + 1) & 0xFF;
}

class EntityManager {
public:
    EntityManager();
    ~EntityManager() = default;

    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isValid(Entity entity) const;

private:
    static constexpr size_t MAX_GEN_ENTITIES = 1024;
    std::array<uint32_t, MAX_GEN_ENTITIES> generations_{};
    size_t nextIndex_ = 1;
};
