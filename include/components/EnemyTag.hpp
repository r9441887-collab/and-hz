#pragma once

enum class EnemyType : unsigned char {
    SKELETON,
    SLIME,
    BAT,
    GOLEM,
    WRAITH,
    DRAGON_BOSS,
    FIRE_ELEMENTAL,
    CULTIST
};

struct EnemyTagComponent {
    EnemyType type = EnemyType::SKELETON;
    int exp = 0;
    float detectionRange = 96.0f;

    EnemyTagComponent() = default;
    EnemyTagComponent(EnemyType type_, int exp_, float detectRange_ = 96.0f)
        : type(type_), exp(exp_), detectionRange(detectRange_) {}
};
