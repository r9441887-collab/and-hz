#pragma once
#include "../core/ECS.hpp"

class TitleScreen {
public:
    TitleScreen();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input, GameState& nextState);
private:
    static constexpr float FADE_IN_DURATION = 1.0f;
    float fadeTimer = 0;
    bool fadeComplete = false;
    int selectedOption = 0;
    std::vector<std::string> menuOptions = {"New Game", "Continue", "Settings", "Quit"};
    struct AshParticle {
        Vec2 pos;
        float speed;
        float size;
        float alpha;
    };
    std::vector<AshParticle> ashParticles;
    void initAshParticles();
    void updateAshParticles(float dt);
    void renderAshParticles(PixelBuffer& buffer);
    void renderLogo(PixelBuffer& buffer, float alpha);
    void renderMenu(PixelBuffer& buffer, float alpha);
};
