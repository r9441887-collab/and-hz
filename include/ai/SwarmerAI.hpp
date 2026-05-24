#pragma once
#include "AIStateMachine.hpp"

class SwarmerAI : public AIStateMachine {
public:
    void update(World& world, Entity self, float dt) override;
    AIState getDefaultState() const override { return AIState::CHASE; }
private:
    static constexpr float SEPARATION_DIST = 24.0f;
    static constexpr float ALIGNMENT_DIST = 60.0f;
    static constexpr float COHESION_DIST = 80.0f;
    static constexpr float MAX_SPEED = 180.0f;
    static constexpr float SEPARATION_FORCE = 200.0f;
    static constexpr float ALIGNMENT_FORCE = 50.0f;
    static constexpr float COHESION_FORCE = 30.0f;

    Vec2 computeSeparation(World& world, Entity self);
    Vec2 computeAlignment(World& world, Entity self);
    Vec2 computeCohesion(World& world, Entity self);
    Vec2 seekPlayer(World& world, Entity self);
    int countAlliesNearby(World& world, Entity self, float radius);
};
