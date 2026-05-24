#pragma once
#include <cstdint>
#include "Particle.hpp"

class PixelBuffer;
class Camera;

template<typename T, int N>
class ObjectPool {
public:
    ObjectPool() : poolSize_(0) {}

    T* alloc() {
        for (int i = 0; i < N; ++i) {
            if (!pool_[i].isAlive()) {
                pool_[i] = T();
                if (i >= poolSize_) poolSize_ = i + 1;
                return &pool_[i];
            }
        }
        return nullptr;
    }

    T* get(int i) { return &pool_[i]; }
    int size() const { return poolSize_; }

    void clear() {
        for (int i = 0; i < N; ++i) {
            pool_[i] = T();
        }
        poolSize_ = 0;
    }

private:
    T pool_[N];
    int poolSize_;
};

class ParticleSystem {
public:
    ParticleSystem();

    void emitExplosion(float x, float y, int count,
                       uint32_t color, float speed, int lifetime);
    void emitTrail(float x, float y, uint32_t color);
    void emitBlood(float x, float y, int count);
    void emitSpark(float x, float y, int count);

    void update(float dt);
    void render(PixelBuffer& buf, class Camera& cam);

private:
    ObjectPool<Particle, 1000> pool_;
};
