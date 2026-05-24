#pragma once
#include "../core/ECS.hpp"

class GameOverScreen {
public:
    GameOverScreen();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input, GameState& nextState);
    void setStats(const PlayerComponent& player);
private:
    int floor = 1;
    int kills = 0;
    float damageDealt = 0;
    float damageTaken = 0;
    float runTime = 0;
    float shakeTimer = 0;
    float shakeIntensity = 5.0f;
    float totalTime = 0;
    int selectedOption = 0;
    std::vector<std::string> options = {"New Run", "Title Screen"};
    void renderShakeText(PixelBuffer& buffer, const std::string& text, int x, int y, const Color& color, int size);
    void renderStats(PixelBuffer& buffer);
};
