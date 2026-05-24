#pragma once
#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>

class Random {
public:
    static Random& instance();

    void seed(uint64_t s);
    void seedFromDevice();

    int nextInt(int min, int max);
    float nextFloat();
    bool chance(float probability);

    template<typename T>
    void shuffle(std::vector<T>& vec) {
        for (size_t i = vec.size(); i > 1; --i) {
            size_t j = static_cast<size_t>(nextInt(0, static_cast<int>(i) - 1));
            std::swap(vec[i - 1], vec[j]);
        }
    }

    template<typename T>
    T& pickRandom(std::vector<T>& vec) {
        return vec[static_cast<size_t>(nextInt(0, static_cast<int>(vec.size()) - 1))];
    }

    template<typename T>
    const T& pickRandom(const std::vector<T>& vec) {
        return vec[static_cast<size_t>(nextInt(0, static_cast<int>(vec.size()) - 1))];
    }

private:
    Random() = default;
    ~Random() = default;
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    uint64_t state_[4]{};

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    uint64_t next();
};
