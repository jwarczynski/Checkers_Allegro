//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_GAME_ENGINE_UTIL_H
#define CHECKERS_GAME_ENGINE_UTIL_H

#include "types.h"
#include <stdbool.h>

void showBoard(Piece board[8][8]);
bool isNotEndOfGame(Piece board[BOARD_SIZE][BOARD_SIZE]);
void countWhiteAndBlackPieces(Piece board[BOARD_SIZE][BOARD_SIZE], int *whiteCount, int *blackCount);


#endif //CHECKERS_GAME_ENGINE_UTIL_H
