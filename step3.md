# Step 3: Using Transposition Tables

The solution we found works, but we can enhance it by using transposition tables.

Transposition tables are maps that store all the positions we have already explored. Since we are searching for one winning path (all paths are of equal quality, so finding one is sufficient), previously explored paths can be pruned.

To implement this, we need:

1. A method to hash the board that produces the same hash for positions that are identical, even if they are rotated or symmetric.

2. Apply the transposition table into our solution

## 1 - Hashing the board

To hash the board, it's pretty easy : We have to have each bitmap of each rotated state of the board, and then merge them using XOR operations.

Like this, there is low chances for colision and the hash is the same for rotated state of the board.

```
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
```

To rotate a bit board, it's pretty easy to implement :

```
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
```

(this rotating method may not be the more optimized one, but it's suficiently efficient for what we need)

## 2 - Apply transposition table

Perfect, now we just need to put it in the solving method :

```
std::vector<Move> solve(Board board, std::vector<Move> moves)
{
    static std::unordered_map<size_t, bool> transposition_table;

    size_t board_hash = board.hash();
    if (transposition_table.count(board_hash) && transposition_table[board_hash]) 
        return {};

    if (board.check_win()) return moves;

    transposition_table[board_hash] = true;

    ...
}
```

We just added a hash map that group all checked state with a boolean, then at each functions calls, we check if the hashed board is present in the map, and if so, we don't check further. Then, we add the hash to the map.