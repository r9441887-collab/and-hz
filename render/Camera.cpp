#include "../../include/render/Camera.hpp"
#include "../../include/render/PixelBuffer.hpp"
#include <cstdlib>
#include <cmath>

Camera::Camera()
    : x_(0), y_(0), shakeFrames_(0), shakeIntensity_(0.0f),
      shakeOffX_(0), shakeOffY_(0) {}

void Camera::follow(float targetX, float targetY, float smoothness) {
    float sw = static_cast<float>(PixelBuffer::WIDTH);
    float sh = static_cast<float>(PixelBuffer::HEIGHT);
    float idealX = targetX - sw * 0.5f;
    float idealY = targetY - sh * 0.5f;

    if (smoothness > 0.0f) {
        float t = smoothness;
        if (t > 1.0f) t = 1.0f;
        x_ += (idealX - x_) * t;
        y_ += (idealY - y_) * t;
    } else {
        x_ = idealX;
        y_ = idealY;
    }
}

std::pair<int, int> Camera::worldToScreen(float wx, float wy) const {
    int sx = static_cast<int>(wx - x_ + shakeOffX_);
    int sy = static_cast<int>(wy - y_ + shakeOffY_);
    return {sx, sy};
}

std::pair<float, float> Camera::screenToWorld(int sx, int sy) const {
    float wx = sx + x_ - shakeOffX_;
    float wy = sy + y_ - shakeOffY_;
    return {wx, wy};
}

void Camera::shake(int frames, float intensity) {
    shakeFrames_ = frames;
    shakeIntensity_ = intensity;
}

Rect Camera::getViewRect() const {
    float w = static_cast<float>(PixelBuffer::WIDTH);
    float h = static_cast<float>(PixelBuffer::HEIGHT);
    return Rect(x_, y_, w, h);
}

void Camera::update(float dt) {
    (void)dt;
    if (shakeFrames_ > 0) {
        shakeOffX_ = static_cast<int>((std::rand() % 3 - 1) * shakeIntensity_);
        shakeOffY_ = static_cast<int>((std::rand() % 3 - 1) * shakeIntensity_);
        shakeFrames_--;
    } else {
        shakeOffX_ = 0;
        shakeOffY_ = 0;
    }
}
