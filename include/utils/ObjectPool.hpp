#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

template<typename T, size_t N>
class ObjectPool {
    std::array<T, N> pool;
    std::array<bool, N> used{};
    size_t numUsed{0};

public:
    T* acquire() {
        for (size_t i = 0; i < N; ++i) {
            if (!used[i]) {
                used[i] = true;
                ++numUsed;
                return &pool[i];
            }
        }
        return nullptr;
    }

    void release(T* obj) {
        if (!obj) return;
        ptrdiff_t idx = obj - pool.data();
        if (idx >= 0 && static_cast<size_t>(idx) < N && used[idx]) {
            used[idx] = false;
            --numUsed;
        }
    }

    size_t size() const {
        return numUsed;
    }

    size_t capacity() const {
        return N;
    }

    void reset() {
        for (size_t i = 0; i < N; ++i) {
            used[i] = false;
        }
        numUsed = 0;
    }
};
