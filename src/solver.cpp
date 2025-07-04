#include "solver.hpp"

std::vector<Move> solve(Board board, std::vector<Move> moves) 
{
    static std::unordered_map<size_t, bool> transposition_table;

    size_t board_hash = board.hash();
    if (transposition_table.count(board_hash) && transposition_table[board_hash]) return {};

    if (board.check_win()) return moves;

    transposition_table[board_hash] = true;

    std::vector<Move> possible_moves = board.get_possible_moves();

    for (const auto& move : possible_moves) 
    {
        board.play(move);
        moves.push_back(move);

        auto result = solve(board, moves);
        if (!result.empty()) return result;

        moves.pop_back();
        board.undo(move);
    }

    return {};
}
