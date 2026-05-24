#pragma once

enum class WeaponType : unsigned char {
    PISTOL,
    SHOTGUN,
    MACHINEGUN,
    SNIPER,
    FLAMETHROWER,
    ICEWAND,
    LIGHTNINGGUN,
    BOOMERANGGUN,
    ROCKETLAUNCHER,
    VOIDCANNON
};

struct WeaponComponent {
    WeaponType type = WeaponType::PISTOL;
    int ammo = 9999;
    float cooldown = 0.2f;
    float timer = 0.0f;
    int bulletsPerShot = 1;
    float spread = 0.0f;

    WeaponComponent() = default;
    WeaponComponent(WeaponType type_, int ammo_, float cooldown_,
                    int bulletsPerShot_ = 1, float spread_ = 0.0f)
        : type(type_), ammo(ammo_), cooldown(cooldown_),
          bulletsPerShot(bulletsPerShot_), spread(spread_) {}
};
