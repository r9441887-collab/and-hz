#pragma once
#include "AIStateMachine.hpp"

class ChaseAI : public AIStateMachine {
public:
    void update(World& world, Entity self, float dt) override;
    AIState getDefaultState() const override { return AIState::CHASE; }
private:
    void doChase(World& world, Entity self, float dt);
    void doAttack(World& world, Entity self, float dt);
    void avoidObstacles(World& world, Entity self, const Vec2& moveDir, Velocity& vel);
    float attackCooldown = 0;
};
