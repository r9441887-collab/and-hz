#include "../../include/core/Random.hpp"

Random& Random::instance() {
    static Random inst;
    return inst;
}

void Random::seed(uint64_t s) {
    state_[0] = s;
    state_[1] = s * 6364136223846793005ULL + 1442695040888963407ULL;
    state_[2] = state_[1] * 6364136223846793005ULL + 1442695040888963407ULL;
    state_[3] = state_[2] * 6364136223846793005ULL + 1442695040888963407ULL;
}

void Random::seedFromDevice() {
    std::random_device rd;
    uint64_t s = (static_cast<uint64_t>(rd()) << 32) | rd();
    seed(s);
}

uint64_t Random::next() {
    uint64_t result = rotl(state_[1] * 5, 7) * 9;
    uint64_t t = state_[1] << 17;

    state_[2] ^= state_[0];
    state_[3] ^= state_[1];
    state_[1] ^= state_[2];
    state_[0] ^= state_[3];

    state_[2] ^= t;
    state_[3] = rotl(state_[3], 45);

    return result;
}

int Random::nextInt(int min, int max) {
    uint64_t range = static_cast<uint64_t>(max) - min + 1;
    if (range <= 1) return min;
    uint64_t r = next();
    return static_cast<int>(min + static_cast<int>(r % range));
}

float Random::nextFloat() {
    constexpr float inv = 1.0f / 18446744073709551615.0f;
    return static_cast<float>(next() >> 11) * inv;
}

bool Random::chance(float probability) {
    return nextFloat() < probability;
}
