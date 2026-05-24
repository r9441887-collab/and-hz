#pragma once
#include "../core/ECS.hpp"

class CombatSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    void applyDamage(World& world, EntityId target, EntityId source, float damage, bool isCrit, float knockback);
private:
    void handleDeath(World& world, Entity entity, EntityId killer);
    void applyKnockback(World& world, EntityId target, const Vec2& direction, float force);
};
