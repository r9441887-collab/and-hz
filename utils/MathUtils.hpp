#pragma once
#include <cmath>
#include <type_traits>

namespace MathUtils {
    constexpr float PI = 3.14159265358979f;
    constexpr float TWO_PI = 6.28318530717959f;
    constexpr float PI_OVER_2 = 1.57079632679490f;
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / PI;

    template<typename T>
    constexpr T clamp(T val, T min, T max) {
        return val < min ? min : (val > max ? max : val);
    }

    constexpr float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    inline float distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    inline float distanceSq(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return dx * dx + dy * dy;
    }

    inline float normalizeAngle(float radians) {
        float a = std::fmod(radians, TWO_PI);
        if (a < 0) a += TWO_PI;
        return a;
    }

    inline float angleBetween(float x1, float y1, float x2, float y2) {
        return std::atan2(y2 - y1, x2 - x1);
    }

    inline float length(float vx, float vy) {
        return std::sqrt(vx * vx + vy * vy);
    }

    inline void normalize(float& vx, float& vy) {
        float len = std::sqrt(vx * vx + vy * vy);
        if (len > 0.00001f) {
            vx /= len;
            vy /= len;
        }
    }

    constexpr float degToRad(float deg) {
        return deg * DEG_TO_RAD;
    }

    constexpr float radToDeg(float rad) {
        return rad * RAD_TO_DEG;
    }

    inline float approach(float current, float target, float delta) {
        if (current < target) {
            current += delta;
            if (current > target) current = target;
        } else if (current > target) {
            current -= delta;
            if (current < target) current = target;
        }
        return current;
    }
}
