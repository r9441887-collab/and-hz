#pragma once
#include "ecs/Entity.hpp"

enum class AIBehavior : unsigned char {
    IDLE,
    PATROL,
    CHASE,
    ATTACK,
    RETREAT,
    DEAD
};

struct AIComponent {
    AIBehavior behavior = AIBehavior::IDLE;
    float stateTimer = 0.0f;
    Entity target = ENTITY_NULL;

    AIComponent() = default;
    AIComponent(AIBehavior behavior_, Entity target_ = ENTITY_NULL)
        : behavior(behavior_), target(target_) {}
};
