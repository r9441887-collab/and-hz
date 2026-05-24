#pragma once
#include "Types.hpp"
#include <functional>
#include <vector>
#include <algorithm>

struct DamageEvent {
    EntityId target;
    EntityId source;
    float damage;
    bool isCrit;
    float knockback;
    DamageEvent(EntityId t, EntityId s, float d, bool c = false, float k = 0)
        : target(t), source(s), damage(d), isCrit(c), knockback(k) {}
};

struct DeathEvent {
    EntityId entity;
    EntityId killer;
    DeathEvent(EntityId e, EntityId k) : entity(e), killer(k) {}
};

struct PickupEvent {
    EntityId player;
    EntityId pickup;
    PickupType type;
    PickupEvent(EntityId p, EntityId pk, PickupType t) : player(p), pickup(pk), type(t) {}
};

struct RoomClearEvent {
    int gridX, gridY;
    RoomClearEvent(int x, int y) : gridX(x), gridY(y) {}
};

struct WeaponFireEvent {
    EntityId shooter;
    WeaponType weapon;
    Vec2 position;
    Vec2 direction;
    WeaponFireEvent(EntityId s, WeaponType w, const Vec2& p, const Vec2& d)
        : shooter(s), weapon(w), position(p), direction(d) {}
};

struct FloorChangeEvent {
    int newFloor;
    explicit FloorChangeEvent(int f) : newFloor(f) {}
};

class EventBus {
public:
    using Handler = std::function<void(const void*)>;

    template <typename T>
    void subscribe(std::function<void(const T&)> handler) {
        auto wrapper = [handler](const void* e) { handler(*static_cast<const T*>(e)); };
        handlers[std::type_index(typeid(T))].push_back(std::move(wrapper));
    }

    template <typename T>
    void publish(const T& event) {
        auto it = handlers.find(std::type_index(typeid(T)));
        if (it != handlers.end()) {
            for (auto& h : it->second) h(&event);
        }
    }

    template <typename T>
    void unsubscribe() {
        handlers.erase(std::type_index(typeid(T)));
    }

    void clear() { handlers.clear(); }

private:
    std::unordered_map<std::type_index, std::vector<Handler>> handlers;
};
