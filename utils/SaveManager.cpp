#include "../../include/utils/SaveManager.hpp"
#include <fstream>
#include <cstring>

SaveManager::SaveManager(const std::string& path) : filePath(path) {}

bool SaveManager::saveProgress(const ProgressData& data) {
    std::ofstream ofs(filePath, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<const char*>(&data), sizeof(ProgressData));
    return ofs.good();
}

bool SaveManager::loadProgress(ProgressData& data) {
    std::ifstream ifs(filePath, std::ios::binary);
    if (!ifs) return false;
    ifs.read(reinterpret_cast<char*>(&data), sizeof(ProgressData));
    return ifs.good();
}

void SaveManager::deleteSave() {
    std::remove(filePath.c_str());
}

bool SaveManager::hasSave() const {
    std::ifstream ifs(filePath);
    return ifs.good();
}
