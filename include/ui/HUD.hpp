#pragma once
#include "../core/ECS.hpp"
#include "Minimap.hpp"

class HUD {
public:
    HUD();
    void update(World& world, float dt);
    void render(PixelBuffer& buffer, Renderer& renderer);
    void showMessage(const std::string& msg, float duration = 3.0f);
private:
    void renderHealthBar(PixelBuffer& buffer, const HealthComponent& health);
    void renderWeaponInfo(PixelBuffer& buffer, const WeaponComponent& weapon);
    void renderInventory(PixelBuffer& buffer, const PlayerComponent& player);
    void renderMinimap(PixelBuffer& buffer, World& world);
    void renderDashCooldown(PixelBuffer& buffer, const PlayerComponent& player);
    void renderCenterMessage(PixelBuffer& buffer);

    Minimap minimap;
    struct CenterMessage {
        std::string text;
        float timer = 0;
        float duration = 3.0f;
    };
    std::vector<CenterMessage> messages;
};
