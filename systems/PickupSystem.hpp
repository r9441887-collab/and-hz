#pragma once
#include "../core/ECS.hpp"

class PickupSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
private:
    void collectPickup(World& world, Entity player, Entity pickup, PickupComponent& pc);
    void spawnCollectEffect(World& world, const Vec2& pos, const Color& color);
};
