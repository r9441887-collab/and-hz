#pragma once

namespace Config {
    constexpr int GAME_W = 480;
    constexpr int GAME_H = 270;
    constexpr float FIXED_DT = 1.0f / 60.0f;
    constexpr int TILE_SIZE = 16;
    constexpr int PLAYER_SPEED = 120;
    constexpr int PLAYER_MAX_HP = 100;
    constexpr float DASH_COOLDOWN = 2.0f;
    constexpr float DASH_DURATION = 0.2f;
    constexpr float PLAYER_FRICTION = 0.85f;
    constexpr float BULLET_LIFETIME = 2.0f;
    constexpr int MAX_AMMO_PISTOL = 9999;
    constexpr int MAX_AMMO_SHOTGUN = 30;
    constexpr int MAX_AMMO_MACHINEGUN = 200;
    constexpr int MAX_AMMO_SNIPER = 10;
    constexpr int MAX_AMMO_ROCKET = 8;
    constexpr float INVINCIBILITY_TIME = 0.1f;
    constexpr int ROOM_MIN_W = 7;
    constexpr int ROOM_MAX_W = 16;
    constexpr int ROOM_MIN_H = 6;
    constexpr int ROOM_MAX_H = 12;
    constexpr int DUNGEON_MIN_ROOMS = 7;
    constexpr int DUNGEON_MAX_ROOMS = 12;
    constexpr float CRIT_CHANCE = 0.05f;
    constexpr float CRIT_MULTIPLIER = 2.0f;
    constexpr int HUD_MINIMAP_W = 60;
    constexpr int HUD_MINIMAP_H = 40;
}
