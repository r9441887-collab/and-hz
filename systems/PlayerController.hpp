#pragma once
#include "../core/ECS.hpp"

class PlayerController {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    void processInput(World& world, const InputState& input, float dt);

private:
    float aimAngle = 0;
    int currentWeaponSlot = 0;
};
