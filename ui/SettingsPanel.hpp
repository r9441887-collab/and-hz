#pragma once
#include "../core/ECS.hpp"

class SettingsPanel {
public:
    SettingsPanel();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input, GameState& nextState);
private:
    int selectedOption = 0;
    float volume = 100.0f;
    bool fullscreen = false;
    int seed = 0;
    std::vector<std::string> options = {"Volume", "Fullscreen", "Seed", "Reset Progress", "Back"};
    void renderVolumeSlider(PixelBuffer& buffer, int x, int y);
    void renderFullscreenToggle(PixelBuffer& buffer, int x, int y);
    void renderSeedInput(PixelBuffer& buffer, int x, int y);
    void resetProgress();
};
