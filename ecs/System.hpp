#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "World.hpp"

class Renderer;

class System {
public:
    virtual ~System() = default;

    virtual void init(World& world) {}
    virtual void update(World& world, float dt) {}
    virtual void render(World& world, Renderer& renderer) {}
};

class SystemManager {
public:
    SystemManager() = default;
    ~SystemManager() = default;

    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    template<typename T, typename... Args>
    void addSystem(int priority, Args&&... args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        systems_.push_back({priority, std::move(system)});
        std::sort(systems_.begin(), systems_.end(),
            [](const SystemEntry& a, const SystemEntry& b) {
                return a.priority < b.priority;
            });
    }

    void init(World& world);
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);

private:
    struct SystemEntry {
        int priority;
        std::unique_ptr<System> system;
    };

    std::vector<SystemEntry> systems_;
};
