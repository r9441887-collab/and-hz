#include "../../include/systems/MovementSystem.hpp"
#include "../../include/core/Types.hpp"

void MovementSystem::update(World& world, float dt) {
    world.each<Transform, Velocity>([dt](Entity entity, Transform& tf, Velocity& vel) {
        vel.velocity += vel.velocity * 0.5f * dt;
        vel.velocity *= 0.9f;
        if (vel.velocity.lengthSq() < 0.1f) vel.velocity = Vec2{0, 0};
        tf.position += vel.velocity * dt;
    });

    world.each<Transform, Collider>([&world](Entity entity, Transform& tf, Collider& col) {
        if (col.type == ColliderType::TILE || col.isTrigger) return;
        auto* tileMap = world.getComponent<TileMap>(entity);
        if (!tileMap) {
            world.each<TileMap>([&](Entity tileEntity, TileMap& map) {
                tileMap = &map;
            });
            if (!tileMap) return;
        }
        if (col.type == ColliderType::CIRCLE) {
            Vec2 push = pushOutCircle(tf.position, col.radius, *tileMap);
            tf.position += push;
        }
    });
}

Vec2 MovementSystem::pushOutCircle(const Vec2& pos, float radius, const TileMap& map) const {
    Vec2 push{0, 0};
    int tx, ty;
    map.worldToTile(pos, tx, ty);
    int rad = static_cast<int>(std::ceil(radius / map.tileSize)) + 1;
    for (int dy = -rad; dy <= rad; ++dy) {
        for (int dx = -rad; dx <= rad; ++dx) {
            int cx = tx + dx, cy = ty + dy;
            if (!map.isWall(cx, cy)) continue;
            Vec2 tileCenter = map.tileToWorld(cx, cy);
            Vec2 diff = pos - tileCenter;
            float dist = diff.length();
            float minDist = radius + map.tileSize / 2.0f;
            if (dist < minDist && dist > 0) {
                float overlap = minDist - dist;
                push += diff.normalized() * overlap;
            } else if (dist == 0) {
                push.y -= overlap;
            }
        }
    }
    return push;
}

void MovementSystem::render(World& world, Renderer& renderer) {
}
