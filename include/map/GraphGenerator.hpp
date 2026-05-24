#pragma once
#include <cstdint>
#include <vector>
#include <utility>

enum class RoomType : uint8_t {
    NORMAL = 0,
    START = 1,
    BOSS = 2,
    TREASURE = 3,
    SHOP = 4,
    SECRET = 5
};

struct RoomNode {
    int id;
    RoomType type;
    int x, y;
    int w, h;
    bool connected;

    RoomNode() : id(-1), type(RoomType::NORMAL),
                 x(0), y(0), w(0), h(0), connected(false) {}
};

struct GraphEdge {
    int from;
    int to;
};

class GraphGenerator {
public:
    GraphGenerator();

    void generate(int seed, int minRooms, int maxRooms);

    const std::vector<RoomNode>& getNodes() const { return nodes_; }
    const std::vector<GraphEdge>& getEdges() const { return edges_; }

private:
    std::vector<RoomNode> nodes_;
    std::vector<GraphEdge> edges_;

    bool overlaps(const RoomNode& a, const RoomNode& b) const;
};
