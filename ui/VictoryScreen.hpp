#pragma once
#include "../core/ECS.hpp"

class VictoryScreen {
public:
    VictoryScreen();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input, GameState& nextState);
    void setStats(const PlayerComponent& player);
private:
    int floor = 0;
    int kills = 0;
    float damageDealt = 0;
    float damageTaken = 0;
    float runTime = 0;
    float totalTime = 0;
    int selectedOption = 0;
    std::vector<std::string> options = {"New Run", "Title Screen"};
    char calculateRank() const;
    void renderRank(PixelBuffer& buffer);
    void renderStats(PixelBuffer& buffer);
    void renderVictoryText(PixelBuffer& buffer);
    float particleTimer = 0;
};
