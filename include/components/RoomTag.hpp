#pragma once

struct RoomTagComponent {
    int roomId = 0;
    bool cleared = false;

    RoomTagComponent() = default;
    explicit RoomTagComponent(int roomId_, bool cleared_ = false)
        : roomId(roomId_), cleared(cleared_) {}
};
