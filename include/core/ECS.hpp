#pragma once
#include "Types.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <memory>
#include <algorithm>
#include <cassert>

struct Entity {
    EntityId id = INVALID_ENTITY;
    Entity() = default;
    explicit Entity(EntityId id) : id(id) {}
    EntityId getId() const { return id; }
    bool valid() const { return id != INVALID_ENTITY; }
    explicit operator bool() const { return valid(); }
    bool operator==(const Entity& o) const { return id == o.id; }
    bool operator!=(const Entity& o) const { return id != o.id; }
    struct Hash { size_t operator()(const Entity& e) const { return std::hash<EntityId>{}(e.id); } };
};

class World {
public:
    Entity createEntity() {
        EntityId id = ++nextId;
        entities[id] = true;
        return Entity(id);
    }

    void destroyEntity(Entity entity) {
        if (!entity.valid()) return;
        entities.erase(entity.id);
        for (auto& [type, pool] : componentPools) {
            auto& pm = *static_cast<ComponentMap*>(pool.get());
            pm.erase(entity.id);
        }
    }

    bool alive(Entity entity) const {
        return entity.valid() && entities.count(entity.id) > 0;
    }

    template <typename T>
    T& addComponent(Entity entity, T component = {}) {
        auto& pool = getOrCreatePool<T>();
        pool[entity.id] = std::move(component);
        return std::any_cast<T&>(pool[entity.id]);
    }

    template <typename T>
    T* getComponent(Entity entity) {
        if (!entity.valid()) return nullptr;
        auto& pool = getOrCreatePool<T>();
        auto it = pool.find(entity.id);
        if (it != pool.end()) return &std::any_cast<T&>(it->second);
        return nullptr;
    }

    template <typename T>
    const T* getComponent(Entity entity) const {
        if (!entity.valid()) return nullptr;
        auto& pool = const_cast<World*>(this)->getOrCreatePool<T>();
        auto it = pool.find(entity.id);
        if (it != pool.end()) return &std::any_cast<const T&>(it->second);
        return nullptr;
    }

    template <typename T>
    void removeComponent(Entity entity) {
        if (!entity.valid()) return;
        auto& pool = getOrCreatePool<T>();
        pool.erase(entity.id);
    }

    template <typename T>
    void each(std::function<void(Entity, T&)> callback) {
        auto& pool = getOrCreatePool<T>();
        for (auto& [id, comp] : pool) {
            Entity e(id);
            if (entities.count(id)) {
                callback(e, std::any_cast<T&>(comp));
            }
        }
    }

    template <typename T, typename... Rest>
    void each(std::function<void(Entity, T&, Rest&...)> callback) {
        auto& pool1 = getOrCreatePool<T>();
        for (auto& [id, comp1] : pool1) {
            Entity e(id);
            if (!entities.count(id)) continue;
            if (!(hasComponent<Rest>(e) && ...)) continue;
            callback(e, std::any_cast<T&>(comp1),
                (std::any_cast<Rest&>(getOrCreatePool<Rest>()[id]))...);
        }
    }

    template <typename T>
    bool hasComponent(Entity entity) {
        if (!entity.valid()) return false;
        auto& pool = getOrCreatePool<T>();
        return pool.count(entity.id) > 0;
    }

    template <typename T>
    size_t componentCount() {
        auto& pool = getOrCreatePool<T>();
        return pool.size();
    }

    std::vector<Entity> getEntitiesWithRoom(const RoomComponent& room) const {
        std::vector<Entity> result;
        for (auto& [id, alive] : entities) {
            Entity e(id);
            auto* rc = const_cast<World*>(this)->getComponent<RoomComponent>(e);
            if (rc && rc->gridX == room.gridX && rc->gridY == room.gridY)
                result.push_back(e);
        }
        return result;
    }

private:
    using ComponentMap = std::unordered_map<EntityId, std::any>;
    EntityId nextId = 0;
    std::unordered_map<EntityId, bool> entities;
    std::unordered_map<std::type_index, std::unique_ptr<void, void(*)(void*)>> componentPools;

    ComponentMap& getOrCreatePoolByType(std::type_index tidx) {
        auto it = componentPools.find(tidx);
        if (it == componentPools.end()) {
            auto ptr = std::unique_ptr<void, void(*)(void*)>(
                new ComponentMap(), [](void* p) { delete static_cast<ComponentMap*>(p); });
            it = componentPools.emplace(tidx, std::move(ptr)).first;
        }
        return *static_cast<ComponentMap*>(it->second.get());
    }

    template <typename T>
    ComponentMap& getOrCreatePool() {
        return getOrCreatePoolByType(std::type_index(typeid(T)));
    }
};

template <typename... Ts>
struct View {
    World& world;
    View(World& w) : world(w) {}
    void each(std::function<void(Entity, Ts&...)> fn) {
        world.each<Ts...>(std::move(fn));
    }
};
