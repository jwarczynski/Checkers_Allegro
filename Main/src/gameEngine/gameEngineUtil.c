//
// Created by Jj on 07/07/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "gameEngine/gameEngineUtil.h"


void showBoard(Piece board[8][8]) {
    setbuf(stdout, 0);
    printf("   ----------------\n");
    for (int i = 7; i >= 0; --i) {
        printf("%d |", 1 + i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i][j] == EMPTY ? ' ' : board[i][j] == WHITE_PAWN ? 'w' : board[i][j] == BLACK_PAWN ? 'b' : board[i][j] == WHITE_QUEEN ? 'W' : 'B'
            );
        }
        printf("|\n");
    }
    printf("   ----------------\n   A B C D E F G H \n\n");

//    printf("%c ", board[0][0] == EMPTY ? ' ' : board[0][0] == WHITE_PAWN ? 'w' : board[0][0] == BLACK_PAWN ? 'b' : board[0][0] == WHITE_QUEEN ? 'W' : 'B');
}

bool isNotEndOfGame(Piece board[BOARD_SIZE][BOARD_SIZE]) {
    int whiteCount = 0;
    int blackCount = 0;

    countWhiteAndBlackPieces(board, &whiteCount, &blackCount);
    return whiteCount > 0 && blackCount > 0;
}

void countWhiteAndBlackPieces(Piece board[BOARD_SIZE][BOARD_SIZE], int *whiteCount, int *blackCount) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == WHITE_PAWN || board[i][j] == WHITE_QUEEN) {
                (*whiteCount)++;
            } else if (board[i][j] == BLACK_PAWN || board[i][j] == BLACK_QUEEN) {
                (*blackCount)++;
            }
        }
    }
}
