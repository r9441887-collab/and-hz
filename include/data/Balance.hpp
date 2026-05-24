#pragma once
#include <cstdint>

namespace Balance {

int enemyHP(int base, int floor);
int enemyDamage(int base, int floor);
int enemyExp(int base, int floor);
float enemySpeed(float base, int floor);
int dropQualityShift(int floor);
int coinsPerDrop(int floor);
int enemiesPerRoom(int floor);

} // namespace Balance
