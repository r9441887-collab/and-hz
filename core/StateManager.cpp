#include "../../include/core/StateManager.hpp"

StateManager::StateManager() = default;

StateManager::~StateManager() {
    while (!stack_.empty()) {
        stack_.back()->exit();
        stack_.pop_back();
    }
}

void StateManager::push(std::unique_ptr<GameState> state) {
    if (!stack_.empty()) {
        stack_.back()->exit();
    }
    stack_.push_back(std::move(state));
    stack_.back()->enter();
}

void StateManager::pop() {
    if (stack_.empty()) return;
    stack_.back()->exit();
    stack_.pop_back();
    if (!stack_.empty()) {
        stack_.back()->enter();
    }
}

void StateManager::switchTo(std::unique_ptr<GameState> state) {
    if (!stack_.empty()) {
        stack_.back()->exit();
        stack_.pop_back();
    }
    stack_.push_back(std::move(state));
    stack_.back()->enter();
}

void StateManager::update(float dt) {
    if (stack_.empty()) return;
    stack_.back()->update(dt);
}

void StateManager::render(Renderer& renderer) {
    if (stack_.empty()) return;
    for (auto& state : stack_) {
        state->render(renderer);
    }
}

void StateManager::handleInput(const InputState& input) {
    if (stack_.empty()) return;
    stack_.back()->handleInput(input);
}

GameState* StateManager::getCurrentState() {
    if (stack_.empty()) return nullptr;
    return stack_.back().get();
}
