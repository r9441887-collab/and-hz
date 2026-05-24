#pragma once
#include "AIStateMachine.hpp"

class BossAI : public AIStateMachine {
public:
    void update(World& world, Entity self, float dt) override;
    AIState getDefaultState() const override { return AIState::ATTACK; }
private:
    static constexpr float PHASE2_THRESHOLD = 0.66f;
    static constexpr float PHASE3_THRESHOLD = 0.33f;
    static constexpr float ATTACK_INTERVAL = 1.5f;

    int getPhase(float hpPercent) const;
    void executeAttackPattern(World& world, Entity self, int pattern, float dt);
    void bulletSpreadAttack(World& world, Entity self, int count, float speed);
    void circularSlam(World& world, Entity self, float radius, float damage);
    void chargeAttack(World& world, Entity self, const Vec2& dir);
    void beamAttack(World& world, Entity self, const Vec2& dir);
    void summonMinions(World& world, Entity self, int count);
    void enrageMode(World& world, Entity self, float dt);

    float attackTimer = 0;
    int currentPattern = 0;
    bool isCharging = false;
    float chargeTimer = 0;
    Vec2 chargeDir;
    float enrageTimer = 0;
};
