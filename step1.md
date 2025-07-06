# Step 1 : Optimizing the Board

## Part 1 : Board representation

The board can be represented as a binary number, where each bit corresponds to a specific position:  

- **1** indicates the position contains a marble.  
- **0** indicates the position is empty.

<br>

Below is the map showing which positions are indicated by the i-th bit.


||||||||
|-----|-----|-----|-----|-----|-----|-----|
|  <span style="opacity: 0.4;">48</span>  |  <span style="opacity: 0.4;">47</span>  |  **46** |  **45**  |  **44**  |  <span style="opacity: 0.4;">43</span>  |  <span style="opacity: 0.4;">42</span>  |
|  <span style="opacity: 0.4;">41</span>  |  <span style="opacity: 0.4;">40</span>  |  **39**  |  **38**  |  **37**  |  <span style="opacity: 0.4;">36</span>  |  <span style="opacity: 0.4;">35</span>  |
|  **34** |  **33** |  **32** |  **31** |  **30** |  **29** |  **28** |
|  **27** |  **26** |  **25** |  **24** |  **23** |  **22** |  **21** |
|  **20** |  **19** |  **18** |  **17** |  **16** |  **15** |  **14** |
|  <span style="opacity: 0.4;">13</span>  |  <span style="opacity: 0.4;">12</span>  |  11 |   **10** |   **9** |  <span style="opacity: 0.4;">8</span>  |  <span style="opacity: 0.4;">7</span>  |
|  <span style="opacity: 0.4;">6</span>  |  <span style="opacity: 0.4;">5</span>  |   **4** |   **3** |   **2** |  <span style="opacity: 0.4;">1</span> |  <span style="opacity: 0.4;">0</span>  |


With this type of representation, we'll be able to make more efficient calculations.

## Part 2 : Initializing and checking for wins

For initializing the game, we can simply set the value at the good value

#### Initial State:

```
0011100
0011100
1111111
1110111
1111111
0011100
0011100
```

<br>

Checking for wins is also simple, we just compare the curent state of the game with the final state needed for wininng.

#### Final State:

```
0000000
0000000
0000000
0001000
0000000
0000000
0000000
```

## Part 3 : How to play the game

### Step 1 : Defining a Move

A **move** consists of two key components:  

1. **Direction**: The direction in which the marble will move. Possible directions are: **UP**, **DOWN**, **LEFT** and **RIGHT**  

2. **Position**: The index of the marble's current position on the board.

#### Direction and Shift Mapping

Each direction corresponds to a specific shift amount, which determines how far the marble moves on the board:  

- **UP**: +7 (move 1 rows above)  
- **DOWN**: -7 (move 1 rows below)  
- **LEFT**: +1 (move to the left) 
- **RIGHT**: -1 (move to the right)

By using this mapping, we can efficiently find a neighbor in given direction.

### Step 2: Determining Possible Moves

To identify possible moves efficiently, we need to ensure that each move satisfies the following conditions:

1. **Marble Present**: The starting position of the move must contain a marble.

2. **Valid Position**: The move must occur within a playable position on the board. Non-playable positions, such as corners, can be excluded using a mask.

3. **Neighbor in Direction**: There must be a neighboring marble in the specified direction to jump over.

4. **Landing Space Available**: The landing position in the specified direction must be empty.

Efficiently checking these conditions is crucial, as the number of positions and directions to evaluate can be significant. To streamline this process, we use bitwise operations. Let dive into all of them.

**1 - Marble Present :**

This step is not an issue. In fact, all marbles present are already stored in the board representation.

**2 - Valid position :**

To check for valid positions, we use predefined masks for each direction. These masks specify which positions on the board can be affected by a move in the given direction.

**UP**  
```
0000000
0000000
0011100
0011100
1111111
0011100
0011100
```

**DOWN**  
```
0011100
0011100
1111111
0011100
0011100
0000000
0000000
```

**LEFT**  
```
0000100
0000100
0011111
0011111
0011111
0000100
0000100
```

**RIGHT**  
```
0010000
0010000
1111100
1111100
1111100
0010000
0010000
```

**3 - Neighbor Present**

To determine positions where there is a neighboring marble in a given direction, we use bit shifts. This approach efficiently identifies neighbors by shifting the board representation based on the direction.

#### Exemple:

If we shift all bits by a 1 to the left, we obtain a bitmap showing all positions where the original bitmap had a neighbor in the right. 

We can use that for each direction and easily check where there is neighbors using the direction shift map we did earlier

- **UP**: `+7` (move 1 row above)  
- **DOWN**: `-7` (move 1 row below)  
- **LEFT**: `+1` (move to the left)  
- **RIGHT**: `-1` (move to the right)  

#### Formula

```
marbles >> shift[direction]
```

**4 - Space to land :**

For this, we do the exact same thing that for seeing neighbors, but multiplied by 2 (two see two marbles longer) and we negate the result, as we want to see where there is NO marbles

#### Formula

```
~(marbles >> (2 * shift[direction]))
```

### Possible moves :

Combining all those techniques, we can obtain all place we a move is possible, for a given direction using this formula :

```
possible_moves = marbles
    & mask[direction]
    & (marbles >> shift[direction])
    & ~(marbles >> (2 * shift[direction]))
```

This approach is optimized by calculating the whole board in one go, which is really good

#### BONUS

To further optimize move selection, we can prioritize moves based on the marble index in ascending order. This approach ensures that moves affecting the lower part of the board are considered first, followed by moves in the upper part. This ordering is generally more effective than grouping moves by direction (e.g., all UP moves first, then LEFT, RIGHT, and DOWN), which often leads to suboptimal gameplay strategies. By sorting moves by marble index, we can achieve a more strategic and efficient move sequence.

### Step 3: Doing / undoing moves

Last thing we need is to play move and undo them. As we said a move is a combination of a direction, and the index of the position.

After checking the position given is valid for the given move (Same process as for checking possible moves), we have to change the board state.

#### Move Changes:

When a move is played, three changes occur on the board:

  1. **Played Marble**: The bit corresponding to the marble's starting position is turned off (indicating the marble has moved).

  2. **Neighbor Marble**: The bit corresponding to the neighboring marble is turned off (indicating the marble has been removed).

  3. **Landing Position**: The bit corresponding to the landing position is turned on (indicating the marble has moved to this position).

So to conclude, as those three bits are changed, we can use the XOR operation to update them.

#### Formula

```
  int offset = directionOffsets[moove.direction];

  marbles ^= 
      (1ULL << moove.index) 
      | (1ULL << (moove.index + offset))
      | (1ULL << (moove.index + 2 * offset));
```

The same process can be repeated for undoing move.

Now we have a fully functional and optimized game board, we can try to solve the game !