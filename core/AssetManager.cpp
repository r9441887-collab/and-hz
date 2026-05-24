#include "../../include/core/AssetManager.hpp"
#include "../../include/core/Logger.hpp"
#include <algorithm>

AssetManager::AssetManager() {
    initAllSprites();
}

AssetManager::~AssetManager() = default;

Sprite* AssetManager::get(std::string_view name) {
    auto it = sprites_.find(std::string(name));
    if (it != sprites_.end()) {
        return it->second.get();
    }
    VB_LOG_WARN("Sprite not found: ", name);
    return nullptr;
}

void AssetManager::loadSprite(std::string_view name, int w, int h) {
    auto sprite = std::make_unique<Sprite>();
    sprite->width = w;
    sprite->height = h;
    sprites_[std::string(name)] = std::move(sprite);
    VB_LOG_DEBUG("Loaded sprite: ", name, " (", w, "x", h, ")");
}

void AssetManager::initAllSprites() {
    loadSprite("player_idle", 16, 16);
    loadSprite("player_walk", 16, 16);
    loadSprite("player_dash", 16, 16);
    loadSprite("player_dead", 16, 16);

    loadSprite("skeleton_idle", 16, 16);
    loadSprite("skeleton_walk", 16, 16);
    loadSprite("skeleton_attack", 16, 16);
    loadSprite("slime_idle", 16, 12);
    loadSprite("slime_jump", 16, 12);
    loadSprite("bat_fly", 16, 12);
    loadSprite("golem_idle", 24, 24);
    loadSprite("golem_attack", 24, 24);
    loadSprite("wraith_idle", 20, 20);
    loadSprite("dragon_idle", 32, 32);
    loadSprite("dragon_attack", 32, 32);
    loadSprite("fire_elemental_idle", 20, 24);
    loadSprite("cultist_idle", 16, 16);
    loadSprite("cultist_cast", 16, 16);

    loadSprite("bullet_pistol", 4, 4);
    loadSprite("bullet_shotgun", 4, 4);
    loadSprite("bullet_machinegun", 3, 3);
    loadSprite("bullet_sniper", 6, 6);
    loadSprite("bullet_rocket", 8, 8);
    loadSprite("bullet_flame", 8, 6);
    loadSprite("bullet_ice", 5, 5);
    loadSprite("bullet_lightning", 6, 10);
    loadSprite("bullet_boomerang", 8, 8);
    loadSprite("bullet_void", 10, 10);

    loadSprite("pickup_heart", 12, 12);
    loadSprite("pickup_coin", 10, 10);
    loadSprite("pickup_ammo", 10, 10);
    loadSprite("pickup_key", 12, 12);
    loadSprite("pickup_bomb", 12, 12);

    loadSprite("hud_heart", 8, 8);
    loadSprite("hud_coin", 8, 8);
    loadSprite("hud_key", 8, 8);
    loadSprite("hud_bomb", 8, 8);
    loadSprite("hud_minimap_frame", 64, 44);

    loadSprite("tile_floor", 16, 16);
    loadSprite("tile_wall", 16, 16);
    loadSprite("tile_door", 16, 16);
    loadSprite("tile_door_open", 16, 16);

    loadSprite("particle_blood", 4, 4);
    loadSprite("particle_spark", 3, 3);
    loadSprite("particle_smoke", 6, 6);

    VB_LOG_INFO("AssetManager initialized with ", sprites_.size(), " sprites");
}
