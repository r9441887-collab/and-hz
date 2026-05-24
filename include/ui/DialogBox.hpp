#pragma once
#include "../core/ECS.hpp"

class DialogBox {
public:
    DialogBox();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void processInput(const InputState& input);
    void showDialog(const std::vector<std::string>& pages);
    void hideDialog();
    bool isActive() const { return active; }
    bool hasNextPage() const { return active && currentPage < pages.size() - 1; }
    void nextPage();
private:
    bool active = false;
    int currentPage = 0;
    std::vector<std::string> pages;
    float textTimer = 0;
    float textSpeed = 0.03f;
    int charsToShow = 0;
    void renderBackground(PixelBuffer& buffer);
    void renderText(PixelBuffer& buffer);
    void renderArrow(PixelBuffer& buffer);
};
