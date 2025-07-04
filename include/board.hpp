#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cstdint>
#include <cassert>
#include <functional>

#include <move.hpp>

// Binary board for Marble Solitaire game
class Board 
{
    private: 

        // The binary representation of the board
        uint64_t marbles;

        // Rotate the binary board clockwise by 90 degree
        static uint64_t rotate_clockwise(uint64_t marbles);

        // Check if the given coordinate is valid
        bool is_coordinate_valid(int index) const;

        // Check if the given coordinate is valid
        bool is_move_possible(Move move) const;

    public:
        
        // A mask used to check for valid coordinates
        static constexpr uint64_t valid_coords = 
            0b0011100001110011111111111111111111100111000011100;

        // The initial state of the game
        static constexpr uint64_t initial_state =
            0b0011100001110011111111110111111111100111000011100;

        // The targeted state, needed to win the game
        static constexpr uint64_t final_state =
            0b0000000000000000000000001000000000000000000000000;

        Board() : marbles(initial_state) {}

        // Display the board on the console
        void display() const;

        // Display the board on the console, including the last move
        void display(Move last_move) const;


        // Play a given move on the board
        void play(Move moove);

        // Undo a given move on the board
        void undo(Move moove);

        // Return true if game is won, false else
        bool check_win() const;

        // Return the list of all possible moves
        std::vector<Move> get_possible_moves() const;

        // Hash the game board
        size_t hash() const;
};
