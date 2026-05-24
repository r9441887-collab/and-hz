#pragma once
#include "../core/ECS.hpp"

enum class AIState : uint8_t {
    IDLE, PATROL, CHASE, ATTACK, FLEE, AMBUSH_WAIT, STUNNED, DEAD
};

class AIStateMachine {
public:
    AIStateMachine() = default;
    virtual ~AIStateMachine() = default;
    virtual void update(World& world, Entity self, float dt) = 0;
    virtual AIState getState() const { return state; }
    virtual void setState(AIState newState) { state = newState; }
    virtual AIState getDefaultState() const { return AIState::IDLE; }
protected:
    AIState state = AIState::IDLE;
    Entity findPlayer(World& world);
    Vec2 getPlayerPosition(World& world);
    float distanceToPlayer(World& world, Entity self);
    void moveToward(World& world, Entity self, const Vec2& target, float speed);
    void moveAway(World& world, Entity self, const Vec2& target, float speed);
    void strafeAround(World& world, Entity self, const Vec2& target, float speed, float dt);
    bool canSeePlayer(World& world, Entity self, float range);
};
