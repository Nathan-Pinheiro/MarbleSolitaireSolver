#include "board.hpp"
#include "solver.hpp"

int main() 
{
    Board board;
    std::vector<Move> moves = solve(board);

    if(moves.empty())
    {
        std::cout << "No solution found ..." << std::endl;
        return 1;
    }

    std::cout << "Solution found !" << std::endl;

    for (const auto& move : moves) 
    {
        board.play(move);

        std::cout << "-------" << std::endl;
        board.display(move);
    }

    return 0;
}