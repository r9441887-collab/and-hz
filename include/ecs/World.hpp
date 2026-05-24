#pragma once
#include <unordered_map>
#include <memory>
#include <tuple>
#include <typeindex>
#include <functional>
#include "Entity.hpp"
#include "Component.hpp"
#include "ComponentStorage.hpp"

class World {
public:
    World();
    ~World();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isValid(Entity entity) const;

    template<typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        auto storage = getOrCreateStorage<T>();
        T comp(std::forward<Args>(args)...);
        storage->add(entity, std::move(comp));
    }

    template<typename T>
    T& getComponent(Entity entity) {
        auto storage = getOrCreateStorage<T>();
        return storage->get(entity);
    }

    template<typename T>
    bool hasComponent(Entity entity) const {
        auto it = storages_.find(std::type_index(typeid(T)));
        if (it == storages_.end()) return false;
        return static_cast<ComponentStorage<T>*>(it->second.get())->has(entity);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        auto it = storages_.find(std::type_index(typeid(T)));
        if (it != storages_.end()) {
            static_cast<ComponentStorage<T>*>(it->second.get())->remove(entity);
        }
    }

    template<typename... Ts>
    void each(std::function<void(Entity, Ts&...)> callback) {
        auto& primaryStorage = *getOrCreateStorage<std::tuple_element_t<0, std::tuple<Ts...>>>();
        primaryStorage.forEach([&](Entity entity, auto& primary) {
            if ((hasComponent<Ts>(entity) && ...)) {
                callback(entity, getComponent<Ts>(entity)...);
            }
        });
    }

private:
    EntityManager entityManager_;
    std::unordered_map<std::type_index, std::unique_ptr<void>> storages_;

    template<typename T>
    ComponentStorage<T>* getOrCreateStorage() {
        auto key = std::type_index(typeid(T));
        auto it = storages_.find(key);
        if (it == storages_.end()) {
            auto storage = std::make_unique<ComponentStorage<T>>();
            auto ptr = storage.get();
            storages_[key] = std::move(storage);
            return ptr;
        }
        return static_cast<ComponentStorage<T>*>(it->second.get());
    }

    template<typename T>
    const ComponentStorage<T>* getStorage() const {
        auto it = storages_.find(std::type_index(typeid(T)));
        if (it == storages_.end()) return nullptr;
        return static_cast<const ComponentStorage<T>*>(it->second.get());
    }
};
