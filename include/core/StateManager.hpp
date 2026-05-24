#pragma once
#include <memory>
#include <vector>
#include "GameState.hpp"

class Renderer;
struct InputState;

class StateManager {
public:
    StateManager();
    ~StateManager();

    void push(std::unique_ptr<GameState> state);
    void pop();
    void switchTo(std::unique_ptr<GameState> state);

    void update(float dt);
    void render(Renderer& renderer);
    void handleInput(const InputState& input);

    GameState* getCurrentState();

private:
    std::vector<std::unique_ptr<GameState>> stack_;
};
