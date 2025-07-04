#pragma once

#include <vector>
#include "board.hpp"

#include <unordered_map>

// In this game, each move remove exactly a marble, so there is no path better than another, all are same speed.
// That said, we find one, we don't have to find a better one.

std::vector<Move> solve(Board board, std::vector<Move> moves = {});