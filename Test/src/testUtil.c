//
// Created by Jj on 21/07/2023.
//

#include "../include/testUtil.h"
#include "types.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void setALlBoardToEmpty() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE ; j++) {
            board[i][j] = EMPTY;
        }
    }
}