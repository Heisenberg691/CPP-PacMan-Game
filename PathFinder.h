// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <vector>
#include <functional>
#include <set>

namespace PathFinder
{
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates_);
    };

    using uint32_t = uint32_t;
    using HeuristicFunction = std::function<uint32_t(Vec2i, Vec2i)>;
    using CoordinateList = std::vector<Vec2i>;

    struct Node
    {
        uint32_t G, H;
        Vec2i coordinates;
        Node* parent;

        Node(Vec2i coord_, Node* parent_ = nullptr);
        uint32_t getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
        bool detectCollision(Vec2i coordinates_);
        bool detectCollision(Vec2i coordinates_, CoordinateList collisions);
        Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator();
        void setWorldSize(Vec2i worldSize_);
        void setDiagonalMovement(bool enable_);
        void setHeuristic(HeuristicFunction heuristic_);
        CoordinateList findPath(Vec2i source_, Vec2i target_);
        CoordinateList findPath(Vec2i source_, Vec2i target_, CoordinateList addonCollisions);
        void addCollision(Vec2i coordinates_);
        void removeCollision(Vec2i coordinates_);
        void clearCollisions();

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        Vec2i worldSize;
        uint32_t directions;
    };

    class Heuristic
    {
        static Vec2i getDelta(Vec2i source_, Vec2i target_);

    public:
        static uint32_t manhattan(Vec2i source_, Vec2i target_);
        static uint32_t euclidean(Vec2i source_, Vec2i target_);
        static uint32_t octagonal(Vec2i source_, Vec2i target_);
    };
}
