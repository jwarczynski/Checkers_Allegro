//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

#include "types.h"

PieceMoves *getMoves(Piece board[BOARD_SIZE][BOARD_SIZE], Position position);

PieceMoves *getBlackMoves(Piece *board[BOARD_SIZE], Position position);
PieceMoves *getWhiteMoves(Piece *board[BOARD_SIZE], Position position);

#endif //CHECKERS_MOVE_H
