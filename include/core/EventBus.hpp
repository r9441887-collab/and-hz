#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include <typeindex>
#include "ecs/Entity.hpp"

struct EnemyKilled {
    Entity entity;
};

struct PlayerDamaged {
    int amount;
};

struct ItemPickedUp {
    Entity entity;
};

struct RoomCleared {
    int roomId;
};

struct BossDefeated {
    Entity entity;
};

struct LevelChanged {
    int floor;
};

class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    template<typename E>
    void emit(E& event) {
        auto it = handlers_.find(std::type_index(typeid(E)));
        if (it != handlers_.end()) {
            for (auto& handler : it->second) {
                auto typedHandler = reinterpret_cast<std::function<void(E&)>*>(handler.get());
                (*typedHandler)(event);
            }
        }
    }

    template<typename E>
    void emit(const E& event) {
        E copy = event;
        emit(copy);
    }

    template<typename E>
    void subscribe(std::function<void(E&)> callback) {
        auto key = std::type_index(typeid(E));
        using FuncType = std::function<void(E&)>;
        auto stored = std::make_unique<FuncType>(std::move(callback));
        handlers_[key].push_back(std::move(stored));
    }

private:
    std::unordered_map<
        std::type_index,
        std::vector<std::unique_ptr<void>>
    > handlers_;
};
