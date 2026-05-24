#pragma once

enum class DamageType : unsigned char {
    PHYSICAL,
    MAGIC,
    FIRE,
    ICE,
    LIGHTNING,
    POISON
};

struct DamageComponent {
    int amount = 0;
    DamageType type = DamageType::PHYSICAL;

    DamageComponent() = default;
    DamageComponent(int amount_, DamageType type_ = DamageType::PHYSICAL)
        : amount(amount_), type(type_) {}
};
