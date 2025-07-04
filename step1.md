### Step 1: Optimizing the Board

The board can be represented as a binary number, where each bit corresponds to a specific position:  

- **1** indicates the position is filled.  
- **0** indicates the position is empty.

<br>

**Mapping of Positions to Bits:**  

|     |     |     |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |  46 |  45 |  44 |     |     |
|     |     |  39 |  38 |  37 |     |     |
|  34 |  33 |  32 |  31 |  30 |  29 |  28 |
|  27 |  26 |  25 |  24 |  23 |  22 |  21 |
|  20 |  19 |  18 |  17 |  16 |  15 |  14 |
|     |     |  11 |  10 |   9 |     |     |
|     |     |   4 |   3 |   2 |     |     |
|     |     |     |     |     |     |     |


With this type of representation, we'll be able to make more efficient calculations.

<br>

**First, we can identify some important numbers**

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

With this, we can initialize our board, and easily check if the game is won

<br>

**Then, we'll have to define how to play :**

A **move** can be defined as : 
 
  - A direction : (UP, DOWN, LEFT, RIGHT)
  - A position : (the position of the marble to move)

<br>

**To be valid, a move has to :**

  - **Be in a valid position** : in fact, corner are understood in our board, but the cannot be played, so we can can remove them with a mask

  - **Point on a marble** : it must point a bit which is on

  - **Have a neighbor in the direction** : it must have a neighbor in the given direction to jump on

  - **Have a landing place** : it must have a neighbor in the given direction to jump on

<br>

**To check that, we can use masks and bits shift :**

#### Valid Positions: (all position where a marble can go)

```
0011100
0011100
1111111
1111111
1111111
0011100
0011100
```

With this mask, we can shift a bit by the position of the given move, and check if the index is on the board.

<br>

Then, we can get the neighbor by shifting by a value depending on the direction :

  - UP : +7
  - DOWN : -7
  - LEFT : +7
  - RIGHT : -7


Each move will change three bits :

  - The position of the moved marble : on -> off
  - The jumped marble : on -> off
  - The position where the marble move : off -> on

We can also get some masks