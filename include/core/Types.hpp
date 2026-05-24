#pragma once
#include "Math.hpp"
#include <string>
#include <vector>
#include <cstdint>

using EntityId = uint32_t;
static constexpr EntityId INVALID_ENTITY = 0;

enum class EnemyType : uint8_t { CHASER, RANGED, SWARMER, BOSS, AMBUSH };
enum class WeaponType : uint8_t {
    PISTOL, SHOTGUN, SNIPER_RIFLE, FLAME_THROWER, ICE_STAFF,
    LIGHTNING_GUN, ROCKET_LAUNCHER, VOID_CANNON, BOOMERANG, BLASTER
};
enum class BulletType : uint8_t {
    PISTOL, SHOTGUN_PELLET, SNIPER, FLAME, ICE_SHARD,
    LIGHTNING_ARC, ROCKET, VOID_ORB, BOOMERANG
};
enum class PickupType : uint8_t { HEART, COIN, AMMO, KEY, WEAPON_DROP, BOMB };
enum class StatusEffectType : uint8_t { BURNING, FROZEN, POISONED, STUNNED };
enum class RoomState : uint8_t { LOCKED, ENEMIES, CLEARED, BOSS, REWARD };
enum class GameState : uint8_t { TITLE, PLAYING, PAUSED, GAME_OVER, VICTORY, SETTINGS, DIALOG, TRANSITION };

struct Transform {
    Vec2 position;
    Vec2 scale{1, 1};
    float rotation = 0;
    Transform() = default;
    explicit Transform(const Vec2& pos) : position(pos) {}
    Transform(const Vec2& pos, float rot) : position(pos), rotation(rot) {}
};

struct Velocity {
    Vec2 velocity;
    float speed = 0;
    Velocity() = default;
    explicit Velocity(const Vec2& v) : velocity(v) {}
};

enum class ColliderType : uint8_t { CIRCLE, RECT, TILE };
struct Collider {
    ColliderType type = ColliderType::CIRCLE;
    float radius = 8.0f;
    Vec2 size{16, 16};
    bool isTrigger = false;
    bool isSolid = true;
    Collider() = default;
    static Collider circle(float r) { Collider c; c.type = ColliderType::CIRCLE; c.radius = r; return c; }
    static Collider rect(float w, float h) { Collider c; c.type = ColliderType::RECT; c.size = {w, h}; return c; }
    Circle getCircle(const Vec2& pos) const { return {pos, radius}; }
};

struct DamageComponent {
    float damage = 0;
    EntityId owner = INVALID_ENTITY;
    bool isCrit = false;
    float knockback = 0;
    DamageComponent() = default;
    DamageComponent(float dmg, EntityId own, bool crit = false, float kb = 0)
        : damage(dmg), owner(own), isCrit(crit), knockback(kb) {}
};

struct HealthComponent {
    float hp = 100;
    float maxHp = 100;
    float invincibilityTimer = 0;
    bool alive = true;
    bool invincible = false;
    HealthComponent() = default;
    explicit HealthComponent(float maxHp) : hp(maxHp), maxHp(maxHp) {}
    void takeDamage(float dmg) {
        if (invincible || invincibilityTimer > 0) return;
        hp -= dmg;
        invincibilityTimer = 0.1f;
        if (hp <= 0) { hp = 0; alive = false; }
    }
    void heal(float amount) { hp = std::min(hp + amount, maxHp); }
    float getPercent() const { return maxHp > 0 ? hp / maxHp : 0; }
};

struct PlayerComponent {
    int bombs = 3;
    int keys = 0;
    int coins = 0;
    int floor = 1;
    float dashCooldown = 0;
    float dashTimer = 0;
    bool isDashing = false;
    bool invincible = false;
    float invincibilityTimer = 0;
    bool showMinimap = false;
    int kills = 0;
    float damageDealt = 0;
    float damageTaken = 0;
    float runTime = 0;
};

struct WeaponComponent {
    WeaponType type = WeaponType::PISTOL;
    float cooldownTimer = 0;
    int ammo = 0;
    int maxAmmo = 0;
    float damageMultiplier = 1.0f;
    WeaponComponent() = default;
    WeaponComponent(WeaponType t, int maxAmmo) : type(t), ammo(maxAmmo), maxAmmo(maxAmmo) {}
    bool canFire() const { return cooldownTimer <= 0 && ammo > 0; }
    void fire() { if (ammo > 0) { --ammo; cooldownTimer = getCooldown(); } }
    float getCooldown() const;
};

struct ProjectileTag {
    BulletType type = BulletType::PISTOL;
    EntityId owner = INVALID_ENTITY;
    float lifetime = 0;
    float maxLifetime = 0;
    bool pierced = false;
    bool returning = false;
    bool exploded = false;
    int pierceCount = 0;
    int chainCount = 0;
    ProjectileTag() = default;
    ProjectileTag(BulletType bt, EntityId own, float life)
        : type(bt), owner(own), lifetime(life), maxLifetime(life) {}
};

struct EnemyComponent {
    EnemyType type = EnemyType::CHASER;
    float detectionRange = 200;
    float attackRange = 50;
    float attackCooldown = 1.0f;
    float attackTimer = 0;
    float damage = 10;
    float speed = 100;
    float xpValue = 10;
    EnemyComponent() = default;
    explicit EnemyComponent(EnemyType t) : type(t) {}
};

struct StatusEffect {
    StatusEffectType type = StatusEffectType::BURNING;
    float duration = 0;
    float timer = 0;
    float tickRate = 1.0f;
    float tickTimer = 0;
    float value = 0;
    StatusEffect() = default;
    StatusEffect(StatusEffectType t, float dur, float val, float tick = 1.0f)
        : type(t), duration(dur), timer(dur), tickRate(tick), tickTimer(tick), value(val) {}
    bool expired() const { return timer <= 0; }
    void update(float dt) { timer -= dt; if (timer < 0) timer = 0; }
    bool canTick() { if (tickTimer <= 0) { tickTimer = tickRate; return true; } tickTimer -= 0.016f; return false; }
};

struct StatusEffectComponent {
    std::vector<StatusEffect> effects;
    void addEffect(StatusEffectType t, float dur, float val, float tick = 1.0f) {
        for (auto& e : effects) {
            if (e.type == t) { e.timer = dur; e.duration = dur; e.value = val; return; }
        }
        effects.emplace_back(t, dur, val, tick);
    }
    void removeEffect(StatusEffectType t) {
        effects.erase(std::remove_if(effects.begin(), effects.end(),
            [t](const StatusEffect& e) { return e.type == t; }), effects.end());
    }
    bool hasEffect(StatusEffectType t) const {
        for (auto& e : effects) if (e.type == t && !e.expired()) return true;
        return false;
    }
    void update(float dt) {
        for (auto& e : effects) e.update(dt);
        effects.erase(std::remove_if(effects.begin(), effects.end(),
            [](const StatusEffect& e) { return e.expired(); }), effects.end());
    }
    Color getTint() const {
        if (hasEffect(StatusEffectType::BURNING)) return {255, 100, 0};
        if (hasEffect(StatusEffectType::FROZEN)) return {100, 200, 255};
        if (hasEffect(StatusEffectType::POISONED)) return {0, 255, 50};
        if (hasEffect(StatusEffectType::STUNNED)) return {200, 200, 0};
        return {255, 255, 255};
    }
};

struct PickupComponent {
    PickupType type = PickupType::HEART;
    WeaponType weaponType = WeaponType::PISTOL;
    float value = 0;
    bool collected = false;
    PickupComponent() = default;
    explicit PickupComponent(PickupType t) : type(t) {}
};

struct RoomComponent {
    int gridX = 0, gridY = 0;
    int width = 0, height = 0;
    RoomState state = RoomState::LOCKED;
    std::vector<EntityId> enemies;
    std::vector<EntityId> doors;
    std::vector<EntityId> spawnedEnemies;
    bool isBossRoom = false;
    bool entered = false;
    bool cleared = false;
    Vec2 worldPos;
    RoomComponent() = default;
};

struct TileMap {
    std::vector<int> tiles;
    int width = 0, height = 0;
    int tileSize = 16;
    bool isWall(int x, int y) const {
        if (x < 0 || y < 0 || x >= width || y >= height) return true;
        return tiles[y * width + x] == 0;
    }
    bool isWalkable(int x, int y) const { return !isWall(x, y); }
    Vec2 tileToWorld(int tx, int ty) const { return {tx * static_cast<float>(tileSize) + tileSize / 2.0f, ty * static_cast<float>(tileSize) + tileSize / 2.0f}; }
    void worldToTile(const Vec2& pos, int& tx, int& ty) const {
        tx = static_cast<int>(pos.x) / tileSize;
        ty = static_cast<int>(pos.y) / tileSize;
    }
    bool isWallAt(const Vec2& pos) const { int tx, ty; worldToTile(pos, tx, ty); return isWall(tx, ty); }
};

struct InputState {
    bool up = false, down = false, left = false, right = false;
    bool shoot = false, bomb = false, reload = false, interact = false;
    bool dash = false, weaponSwitchQ = false, minimapToggle = false, pause = false;
    float mouseX = 0, mouseY = 0;
    int scrollDelta = 0;
    bool weaponSwitchUp = false, weaponSwitchDown = false;
};

struct Renderer { int dummy = 0; };

struct SpriteComponent {
    std::string spriteName;
    Color tint{255, 255, 255};
    float alpha = 1.0f;
    int layer = 0;
    bool visible = true;
    Vec2 origin{0.5f, 0.5f};
    SpriteComponent() = default;
    explicit SpriteComponent(const std::string& name) : spriteName(name) {}
};

struct DialogComponent {
    std::vector<std::string> pages;
    int currentPage = 0;
    bool active = false;
    DialogComponent() = default;
};

struct BossComponent {
    int phase = 1;
    float attackTimer = 0;
    int attackPattern = 0;
    bool enraged = false;
    std::vector<EntityId> minions;
    BossComponent() = default;
};

struct SpawnComponent {
    float delay = 0;
    float timer = 0;
    bool spawned = false;
    EnemyType enemyType = EnemyType::CHASER;
    SpawnComponent() = default;
};

struct PathNode {
    int x = 0, y = 0;
    float g = 0, h = 0, f = 0;
    PathNode* parent = nullptr;
    PathNode() = default;
    PathNode(int x, int y) : x(x), y(y) {}
    bool operator>(const PathNode& o) const { return f > o.f; }
    bool operator==(const PathNode& o) const { return x == o.x && y == o.y; }
};

struct PixelBuffer {
    std::vector<Color> pixels;
    int width = 0, height = 0;
    PixelBuffer() = default;
    PixelBuffer(int w, int h) : width(w), height(h) { pixels.resize(w * h, Color{0, 0, 0, 0}); }
    void setPixel(int x, int y, Color c) {
        if (x < 0 || y < 0 || x >= width || y >= height) return;
        pixels[y * width + x] = c;
    }
    Color getPixel(int x, int y) const {
        if (x < 0 || y < 0 || x >= width || y >= height) return {};
        return pixels[y * width + x];
    }
    void clear(Color c = {0, 0, 0, 0}) { std::fill(pixels.begin(), pixels.end(), c); }
    void fillRect(int x, int y, int w, int h, Color c) {
        for (int py = y; py < y + h; ++py)
            for (int px = x; px < x + w; ++px)
                setPixel(px, py, c);
    }
};

static constexpr float PI = 3.14159265358979323846f;
static constexpr float DEG_TO_RAD = PI / 180.0f;
static constexpr float RAD_TO_DEG = 180.0f / PI;
static constexpr float TILE_SIZE = 16.0f;
static constexpr int SCREEN_WIDTH = 480;
static constexpr int SCREEN_HEIGHT = 320;
