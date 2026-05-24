#pragma once
#include "../core/ECS.hpp"

class RoomSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    RoomComponent* getCurrentRoom(World& world, Entity player);
    void onRoomEntered(World& world, RoomComponent& room);
    void checkRoomCleared(World& world, RoomComponent& room);
    void spawnReward(World& world, RoomComponent& room);
    void openDoors(World& world, RoomComponent& room);
    void closeDoors(World& world, RoomComponent& room);
};
