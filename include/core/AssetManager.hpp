#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>

struct Sprite {
    int width = 0;
    int height = 0;
    unsigned int textureId = 0;
    float u0 = 0.0f, v0 = 0.0f;
    float u1 = 1.0f, v1 = 1.0f;
};

class AssetManager {
public:
    AssetManager();
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    Sprite* get(std::string_view name);

private:
    std::unordered_map<std::string, std::unique_ptr<Sprite>> sprites_;

    void loadSprite(std::string_view name, int w, int h);
    void initAllSprites();
};
