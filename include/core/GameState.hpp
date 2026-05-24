#pragma once

class Renderer;
struct InputState;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update(float dt) = 0;
    virtual void render(Renderer& renderer) = 0;
    virtual void handleInput(const InputState& input) = 0;
};
