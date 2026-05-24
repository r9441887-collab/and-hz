#pragma once
#include <cstdint>
#include <string>

struct ProgressData {
    uint64_t seed;
    int floor;
    int kills;
    int damageDealt;
    int damageTaken;
    int roomsCleared;
    int floorsCompleted;
    float timePlayed;
};

class SaveManager {
    std::string filePath;
public:
    SaveManager(const std::string& path);
    bool saveProgress(const ProgressData& data);
    bool loadProgress(ProgressData& data);
    void deleteSave();
    bool hasSave() const;
};
