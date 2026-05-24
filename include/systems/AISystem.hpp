#pragma once
#include "../core/ECS.hpp"
#include "../ai/AIController.hpp"

class AISystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
private:
    AIController aiController;
};
