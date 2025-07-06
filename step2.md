# Step 2: Exploring Possible Moves

We have made a optimized game board, now we need to use it to find a solution to this game.

As this game remove one marble at each move, **all positions are considered as optimal**, as they got the **same amount of moves**, so we only need to check for **one wining path**.

To solve this, we'll use a recursive function, that will :

1. Check if the game is won (if so return the result. The path is found !)
2. Check if there is moves to play (else return nothing)
3. Play and repeat the process for each moves
4. If no solution found, we return an empty list

When found, the function will return the list of moves to apply to go from initial position to finished one.

#### Algotithm

```
std::vector<Move> solve(Board board, std::vector<Move> moves)
{
    if (board.check_win()) return moves; // Step 1

    std::vector<Move> possible_moves = board.get_possible_moves(); // Step 2

    for (const auto& move : possible_moves)  // Step 3
    {
        board.play(move);
        moves.push_back(move);

        auto result = solve(board, moves);
        if (!result.empty()) return result;

        moves.pop_back();
        board.undo(move);
    }

    return {}; // Step 4
}
```