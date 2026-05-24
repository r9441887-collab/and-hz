#pragma once
#include "../core/ECS.hpp"

class PauseMenu {
public:
    PauseMenu();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input, GameState& nextState);
private:
    int selectedOption = 0;
    std::vector<std::string> options = {"Resume", "Restart Run", "Settings", "Quit to Title"};
    void renderOverlay(PixelBuffer& buffer);
    void renderMenu(PixelBuffer& buffer);
};
