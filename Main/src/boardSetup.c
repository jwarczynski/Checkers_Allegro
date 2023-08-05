//
// Created by Jj on 07/07/2023.
//

#include <stdio.h>
#include "boardSetup.h"

void setupBoard(Piece board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (i < 3 && (i + j) % 2 == 0) {
                board[i][j] = WHITE_PAWN;
            } else if (i > 4 && (i + j) % 2 == 0) {
                board[i][j] = BLACK_PAWN;
            }
        }
    }
}

Piece decodeChar(char c) {
    switch (c) {
        case 'a':
            return WHITE_PAWN;
        case 'b':
            return BLACK_PAWN;
        case 'A':
            return WHITE_QUEEN;
        case 'B':
            return BLACK_QUEEN;
        default:
            return EMPTY;
    }
}

void read_board(Piece board[BOARD_SIZE][BOARD_SIZE], const char *name) {
    FILE *f = fopen(name, "rt");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char encodedPiece = (char) fgetc(f);
            Piece piece = decodeChar(encodedPiece);
            board[i][j] = piece;
        }
        fgetc(f);
    }
    fclose(f);
}