#pragma once
#include "../core/ECS.hpp"
#include "../weapons/WeaponData.hpp"

class WeaponSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    Entity fireWeapon(World& world, EntityId shooter, WeaponType type, const Vec2& position, const Vec2& direction);
private:
    void firePistol(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireShotgun(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireSniper(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireFlameThrower(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireIceStaff(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireLightningGun(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireRocketLauncher(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireVoidCannon(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireBoomerang(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void fireBlaster(World& world, EntityId shooter, const Vec2& pos, const Vec2& dir);
    void updateCooldowns(World& world, float dt);
};
