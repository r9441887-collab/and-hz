#pragma once
#include <cstdint>
#include <string>
#include <string_view>

namespace EmbeddedSprites {

extern const uint32_t player_idle[256];
extern const uint32_t player_run_0[256];
extern const uint32_t player_run_1[256];
extern const uint32_t player_run_2[256];
extern const uint32_t player_run_3[256];
extern const uint32_t enemy_skeleton[256];
extern const uint32_t enemy_slime[144];
extern const uint32_t enemy_bat[144];
extern const uint32_t enemy_golem[576];
extern const uint32_t enemy_wraith[256];
extern const uint32_t enemy_dragon_boss[1024];
extern const uint32_t enemy_fire_elemental[256];
extern const uint32_t enemy_cultist[256];
extern const uint32_t bullets_pistol[16];
extern const uint32_t bullets_shotgun[9];
extern const uint32_t bullets_magic[25];
extern const uint32_t heart[64];
extern const uint32_t coin[36];
extern const uint32_t ammo[36];
extern const uint32_t key[36];
extern const uint32_t chest_closed[144];
extern const uint32_t chest_open[144];
extern const uint32_t tiles_wall[256];
extern const uint32_t tiles_floor[256];
extern const uint32_t tiles_floor_variant1[256];
extern const uint32_t tiles_floor_variant2[256];
extern const uint32_t tiles_floor_variant3[256];
extern const uint32_t tiles_door_closed[256];
extern const uint32_t tiles_door_open[256];
extern const uint32_t tiles_stairs[256];
extern const uint32_t effects_explosion_0[256];
extern const uint32_t effects_explosion_1[256];
extern const uint32_t effects_explosion_2[256];
extern const uint32_t effects_explosion_3[256];
extern const uint32_t effects_spark[16];
extern const uint32_t effects_smoke[36];

const uint32_t* getEmbeddedData(const std::string& name, int& w, int& h);

} // namespace EmbeddedSprites
