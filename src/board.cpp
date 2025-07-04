#include "board.hpp"

uint64_t Board::rotate_clockwise(uint64_t marbles) 
{
    uint64_t rotated = 0;
    for (int y = 0; y < 7; ++y) 
    {
        for (int x = 0; x < 7; ++x) 
        {
            int old_index = y * 7 + x;
            int new_index = x * 7 + (6 - y);
            if (marbles & (1ULL << old_index)) 
            {
                rotated |= (1ULL << new_index);
            }
        }
    }
    return rotated;
}

bool Board::check_win() const 
{
    return marbles == final_state;
}

void Board::display() const 
{
    for (int y = 0; y < 7; ++y) 
    {
        for (int x = 0; x < 7; ++x) 
        {
            int index = (6 - y) * 7 + (6 - x);
            bool is_valid = (valid_coords & (1ULL << index)) != 0;
            bool has_marble = (marbles & (1ULL << index)) != 0;
            std::cout << (is_valid ? (has_marble ? "O" : ".") : " ");
        }
        std::cout << "\n";
    }
}

void Board::display(Move last_move) const 
{
    for (int y = 0; y < 7; ++y) 
    {
        for (int x = 0; x < 7; ++x) 
        {
            int index = (6 - y) * 7 + (6 - x);
            if (last_move.index + directionOffsets[last_move.direction] == index) {
                switch (last_move.direction) 
                {
                    case Direction::UP: std::cout << '^'; break;
                    case Direction::DOWN: std::cout << 'v'; break;
                    case Direction::LEFT: std::cout << '<'; break;
                    case Direction::RIGHT: std::cout << '>'; break;
                }
            }  
            else 
            {
                bool is_valid = (valid_coords & (1ULL << index)) != 0;
                bool has_marble = (marbles & (1ULL << index)) != 0;
                std::cout << (is_valid ? (has_marble ? "O" : ".") : " ");
            }
        }
        std::cout << "\n";
    }
}

bool Board::is_coordinate_valid(int index) const 
{
    return 1ULL << index & valid_coords;
}

bool Board::is_move_possible(Move move) const 
{
    int offset = directionOffsets[move.direction];

    return (marbles & (1ULL << move.index) & directionMask[move.direction]) != 0 &&
           (marbles & (1ULL << (move.index + offset))) != 0 &&
           (marbles & (1ULL << (move.index + 2 * offset))) == 0;
}

void Board::play(Move moove) 
{
    int offset = directionOffsets[moove.direction];

    assert(is_coordinate_valid(moove.index) && "Invalid starting coordinate.");
    assert(is_coordinate_valid(moove.index + offset) && "Invalid intermediate coordinate.");
    assert(is_coordinate_valid(moove.index + 2 * offset) && "Invalid ending coordinate.");
    assert(is_move_possible(moove) && "Move is not possible.");

    marbles ^= (1ULL << moove.index) | (1ULL << (moove.index + offset)) | (1ULL << (moove.index + 2 * offset));
}

void Board::undo(Move moove) 
{
    int offset = directionOffsets[moove.direction];

    assert(is_coordinate_valid(moove.index) && "Invalid starting coordinate.");
    assert(is_coordinate_valid(moove.index + offset) && "Invalid intermediate coordinate.");
    assert(is_coordinate_valid(moove.index + 2 * offset) && "Invalid ending coordinate.");

    marbles ^= (1ULL << moove.index) | (1ULL << (moove.index + offset)) | (1ULL << (moove.index + 2 * offset));
}

std::vector<Move> Board::get_possible_moves() const 
{
    std::vector<Move> possible_moves;

    for (int index = 0; index < 49; ++index) 
    {
        if (!is_coordinate_valid(index)) continue;

        for (const auto& [direction, offset] : directionOffsets) 
        {
            Move moove(index, direction);
            if (!is_coordinate_valid(index + offset)) continue;
            if (!is_coordinate_valid(index + 2 * offset)) continue;
            if (is_move_possible(moove)) possible_moves.push_back(moove);
        }
    }

    return possible_moves;
}

size_t Board::hash() const 
{
    uint64_t rotated1 = Board::rotate_clockwise(marbles);
    uint64_t rotated2 = Board::rotate_clockwise(rotated1);
    uint64_t rotated3 = Board::rotate_clockwise(rotated2);

    size_t hash1 = std::hash<uint64_t>{}(marbles);
    size_t hash2 = std::hash<uint64_t>{}(rotated1);
    size_t hash3 = std::hash<uint64_t>{}(rotated2);
    size_t hash4 = std::hash<uint64_t>{}(rotated3);

    return hash1 + (hash2 * 31) + (hash3 * 31 * 31) + (hash4 * 31 * 31 * 31);
}