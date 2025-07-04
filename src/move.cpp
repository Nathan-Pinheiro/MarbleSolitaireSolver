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
    {Direction::UP,     0b1111111111111111111111111111111111111111111111111},
    {Direction::LEFT,   0b0011111001111100111110011111001111100111110011111},
    {Direction::RIGHT,  0b1111100111110011111001111100111110011111001111100},
    {Direction::DOWN,   0b1111111111111111111111111111111111111111111111111},
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