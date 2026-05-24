#pragma once
#include <vector>
#include "WeaponComponent.hpp"

struct InventoryComponent {
    std::vector<WeaponType> weapons = { WeaponType::PISTOL };
    int currentWeaponIdx = 0;
    int coins = 0;
    int bombs = 0;

    InventoryComponent() = default;

    WeaponType getCurrentWeapon() const {
        if (weapons.empty()) return WeaponType::PISTOL;
        return weapons[currentWeaponIdx];
    }
};
