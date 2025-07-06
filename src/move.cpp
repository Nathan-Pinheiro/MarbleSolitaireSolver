#include "move.hpp"

std::map<Direction, int> directionOffsets = 
{
    {Direction::UP, 7},
    {Direction::LEFT, 1},
    {Direction::RIGHT, -1},
    {Direction::DOWN, -7},
};

std::map<Direction, uint64_t> directionMask = 
{
    {Direction::UP,     0b0000000000000000111000011100111111100111000011100},
    {Direction::LEFT,   0b0000100000010000111110011111001111100001000000100},
    {Direction::RIGHT,  0b0010000001000011111001111100111110000100000010000},
    {Direction::DOWN,   0b0011100001110011111110011100001110000000000000000},
};

Move::Move(uint8_t index, Direction direction) : index(index), direction(direction) {}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    const char* result = nullptr;
    switch (move.direction) {
        case Direction::UP: result = "UP"; break;
        case Direction::DOWN: result = "DOWN"; break;
        case Direction::LEFT: result = "LEFT"; break;
        case Direction::RIGHT: result = "RIGHT"; break;
    }

    os << static_cast<int>(move.index);
    if (move.index < 10) os << ' ';
    os << " : " << result;

    return os;
}