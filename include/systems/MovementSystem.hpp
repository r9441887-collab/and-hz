#pragma once
#include "../core/ECS.hpp"

class MovementSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
};
