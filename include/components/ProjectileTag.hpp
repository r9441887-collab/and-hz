#pragma once
#include "ecs/Entity.hpp"
#include "Damage.hpp"

struct ProjectileTagComponent {
    Entity owner = ENTITY_NULL;
    float damage = 1.0f;
    float speed = 300.0f;
    DamageType type = DamageType::PHYSICAL;
    float lifetime = 2.0f;

    ProjectileTagComponent() = default;
    ProjectileTagComponent(Entity owner_, float damage_, float speed_,
                           DamageType type_ = DamageType::PHYSICAL,
                           float lifetime_ = 2.0f)
        : owner(owner_), damage(damage_), speed(speed_),
          type(type_), lifetime(lifetime_) {}
};
