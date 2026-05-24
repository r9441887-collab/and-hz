#pragma once
#include "AIStateMachine.hpp"

class AmbushAI : public AIStateMachine {
public:
    void update(World& world, Entity self, float dt) override;
    AIState getDefaultState() const override { return AIState::AMBUSH_WAIT; }
private:
    static constexpr float AMBUSH_RANGE = 2.0f * TILE_SIZE;
    static constexpr float AMBUSH_DAMAGE_MULT = 3.0f;

    bool ambushTriggered = false;
    bool surpriseApplied = false;

    void waitAmbush(World& world, Entity self, float dt);
    void triggerAmbush(World& world, Entity self);
    void doChaseAfterAmbush(World& world, Entity self, float dt);
    float attackCooldown = 0;
};
