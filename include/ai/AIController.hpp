#pragma once
#include "../core/ECS.hpp"
#include <memory>

class AIStateMachine;

class AIController {
public:
    AIController() = default;
    ~AIController() = default;
    void update(World& world, Entity self, float dt);
    void assignAI(Entity entity, EnemyType type, World& world);
    AIStateMachine* getAI(Entity entity);

private:
    std::unordered_map<EntityId, std::unique_ptr<AIStateMachine>> aiMap;
    std::unique_ptr<AIStateMachine> createAI(EnemyType type);
};
