//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_BOARD_SETUP_H
#define CHECKERS_BOARD_SETUP_H

#include "types.h"

void setupBoard(Piece board[BOARD_SIZE][BOARD_SIZE]);
void read_board(Piece board[BOARD_SIZE][BOARD_SIZE], const char *name);

#endif //CHECKERS_BOARD_SETUP_H
