#pragma once
#include "../core/ECS.hpp"

class ProjectileSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
private:
    void updateBulletMovement(World& world, float dt);
    void checkWallCollisions(World& world);
    void updateLifetime(World& world, float dt);
    void handleBoomerang(World& world, Entity entity, ProjectileTag& proj, Transform& tf, float dt);
    void handleRocket(World& world, Entity entity, ProjectileTag& proj, Transform& tf);
    void handleLightning(World& world, Entity entity, ProjectileTag& proj, Transform& tf);
    void destroyBullet(World& world, Entity entity);
};
