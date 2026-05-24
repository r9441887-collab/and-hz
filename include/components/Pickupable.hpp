#pragma once

enum class PickupType : unsigned char {
    HEART,
    COIN,
    AMMO,
    KEY,
    WEAPON_DROP,
    BOMB
};

struct PickupableComponent {
    PickupType type = PickupType::HEART;
    int value = 1;
    float bobTimer = 0.0f;

    PickupableComponent() = default;
    PickupableComponent(PickupType type_, int value_ = 1)
        : type(type_), value(value_) {}
};
