#pragma once
#include <memory>
#include <string>
#include <vector>

class StateManager;
class Renderer;
class AssetManager;
class EventBus;

class Game {
public:
    Game();
    ~Game();

    bool initialize(int argc, char* argv[]);
    void run();
    void shutdown();

    StateManager& getStateManager();
    Renderer& getRenderer();
    AssetManager& getAssetManager();
    EventBus& getEventBus();

private:
    bool fullscreen_ = false;
    unsigned int seed_ = 0;
    bool vSync_ = true;

    std::unique_ptr<StateManager> stateManager_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<AssetManager> assetManager_;
    std::unique_ptr<EventBus> eventBus_;

    bool running_ = false;

    void parseCommandLine(int argc, char* argv[]);
    void fixedUpdate(float dt);
    void variableUpdate(float dt);
    void render();
    void present();

    float accumulator_ = 0.0f;
};
