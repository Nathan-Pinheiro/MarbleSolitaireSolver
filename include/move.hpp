#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cstdint>
#include <cassert>
#include <functional>

enum class Direction {
    UP,
    LEFT,
    RIGHT,
    DOWN,
};

extern std::map<Direction, int> directionOffsets;
extern std::map<Direction, uint64_t> directionMask;

class Move
{
    public:
        uint8_t index;
        Direction direction;

        Move(uint8_t index, Direction direction);

        friend std::ostream& operator<<(std::ostream& os, const Move& move);
};