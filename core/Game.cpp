#include "../../include/core/Game.hpp"
#include "../../include/core/StateManager.hpp"
#include "../../include/core/Time.hpp"
#include "../../include/core/Logger.hpp"
#include "../../include/core/Config.hpp"
#include "../../include/core/Random.hpp"
#include "../../include/core/AssetManager.hpp"
#include "../../include/core/EventBus.hpp"

#include <algorithm>
#include <cstdlib>

// Forward declare a minimal renderer interface for the game loop
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual bool init(const char* title, int width, int height, bool fullscreen) = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
    virtual void present() = 0;
    virtual void shutdown() = 0;
    virtual bool isOpen() const = 0;
};

struct InputState {
    bool keys[256]{};
    bool keysPressed[256]{};
    int mouseX = 0, mouseY = 0;
    bool mouseButtons[3]{};
    bool quit = false;
};

static std::unique_ptr<Renderer> createPlatformRenderer();

Game::Game()
    : stateManager_(std::make_unique<StateManager>())
    , renderer_(createPlatformRenderer())
    , assetManager_(std::make_unique<AssetManager>())
    , eventBus_(std::make_unique<EventBus>())
{
}

Game::~Game() = default;

bool Game::initialize(int argc, char* argv[]) {
    Logger::instance().setLevel(LogLevel::DEBUG);
    VB_LOG_INFO("VOIDBREAKER v1.0 initializing...");

    parseCommandLine(argc, argv);

    if (seed_ == 0) {
        Random::instance().seedFromDevice();
    } else {
        Random::instance().seed(seed_);
    }
    VB_LOG_INFO("Random seed: ", seed_);

    bool rendererOk = renderer_->init("VOIDBREAKER", Config::GAME_W, Config::GAME_H, fullscreen_);
    if (!rendererOk) {
        VB_LOG_ERROR("Failed to initialize renderer");
        return false;
    }

    VB_LOG_INFO("Game initialized successfully");
    return true;
}

void Game::run() {
    running_ = true;
    Time& time = Time::instance();

    while (running_ && renderer_->isOpen()) {
        time.tick();
        float dt = time.getDeltaTime();

        accumulator_ += dt;
        while (accumulator_ >= Config::FIXED_DT) {
            fixedUpdate(Config::FIXED_DT);
            accumulator_ -= Config::FIXED_DT;
        }

        variableUpdate(dt);
        render();
        present();

        if (InputState* state = reinterpret_cast<InputState*>(nullptr)) {
            (void)state;
        }
    }
}

void Game::shutdown() {
    VB_LOG_INFO("VOIDBREAKER shutting down...");
    stateManager_.reset();
    renderer_->shutdown();
    VB_LOG_INFO("Shutdown complete");
}

StateManager& Game::getStateManager() { return *stateManager_; }
Renderer& Game::getRenderer() { return *renderer_; }
AssetManager& Game::getAssetManager() { return *assetManager_; }
EventBus& Game::getEventBus() { return *eventBus_; }

void Game::parseCommandLine(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--fullscreen" || arg == "-f") {
            fullscreen_ = true;
        } else if (arg == "--seed" && i + 1 < argc) {
            seed_ = static_cast<unsigned int>(std::atoi(argv[++i]));
        } else if (arg == "--help" || arg == "-h") {
            VB_LOG_INFO("Usage: voidbreaker [--fullscreen] [--seed NNNN]");
        }
    }
}

void Game::fixedUpdate(float dt) {
    stateManager_->update(dt);
}

void Game::variableUpdate(float dt) {
    InputState input{};
    stateManager_->handleInput(input);
}

void Game::render() {
    renderer_->beginFrame();
    stateManager_->render(*renderer_);
    renderer_->endFrame();
}

void Game::present() {
    renderer_->present();
}

// Platform detection and renderer creation
#if defined(_WIN32)
#include <windows.h>

class Win32Renderer : public Renderer {
public:
    Win32Renderer() = default;
    ~Win32Renderer() override = default;

    bool init(const char* title, int width, int height, bool fullscreen) override {
        VB_LOG_INFO("Win32Renderer initialized: ", title, " ", width, "x", height,
                    fullscreen ? " fullscreen" : " windowed");
        return true;
    }

    void beginFrame() override {}
    void endFrame() override {}
    void present() override {}
    void shutdown() override {}
    bool isOpen() const override { return true; }
};

#elif defined(__linux__)
class LinuxRenderer : public Renderer {
public:
    bool init(const char* title, int width, int height, bool fullscreen) override {
        VB_LOG_INFO("LinuxRenderer initialized: ", title, " ", width, "x", height);
        return true;
    }
    void beginFrame() override {}
    void endFrame() override {}
    void present() override {}
    void shutdown() override {}
    bool isOpen() const override { return true; }
};
#else
class FallbackRenderer : public Renderer {
public:
    bool init(const char* title, int width, int height, bool fullscreen) override {
        VB_LOG_INFO("FallbackRenderer initialized: ", title, " ", width, "x", height);
        return true;
    }
    void beginFrame() override {}
    void endFrame() override {}
    void present() override {}
    void shutdown() override {}
    bool isOpen() const override { return true; }
};
#endif

static std::unique_ptr<Renderer> createPlatformRenderer() {
#if defined(_WIN32)
    return std::make_unique<Win32Renderer>();
#elif defined(__linux__)
    return std::make_unique<LinuxRenderer>();
#else
    return std::make_unique<FallbackRenderer>();
#endif
}
