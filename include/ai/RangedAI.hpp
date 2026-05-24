#pragma once
#include "AIStateMachine.hpp"

class RangedAI : public AIStateMachine {
public:
    void update(World& world, Entity self, float dt) override;
    AIState getDefaultState() const override { return AIState::ATTACK; }
private:
    static constexpr float IDEAL_MIN = 4 * TILE_SIZE;
    static constexpr float IDEAL_MAX = 8 * TILE_SIZE;
    static constexpr float RETREAT_DIST = 3 * TILE_SIZE;
    void maintainDistance(World& world, Entity self, float dt);
    void doStrafe(World& world, Entity self, float dt);
    void retreat(World& world, Entity self, float dt);
    float strafeTimer = 0;
    float strafeDirection = 1;
    float shootTimer = 0;
    Vec2 lastKnownPlayerPos;
};
