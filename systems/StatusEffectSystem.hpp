#pragma once
#include "../core/ECS.hpp"

class StatusEffectSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
private:
    void processBurning(World& world, Entity entity, StatusEffectComponent& sec, HealthComponent& hc, float dt);
    void processFrozen(World& world, Entity entity, StatusEffectComponent& sec, Velocity& vel, float dt);
    void processPoisoned(World& world, Entity entity, StatusEffectComponent& sec, HealthComponent& hc, float dt);
    void processStunned(World& world, Entity entity, StatusEffectComponent& sec, Velocity& vel);
};
