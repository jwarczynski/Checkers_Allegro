//
// Created by Jj on 15/07/2023.
//


#include <malloc.h>
#include "types.h"
#include "moves/moveUtil.h"
#include "moves/moves/pawnMove.h"
#include "moves/move.h"


#define MAX_PAWN_MOVES 2

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


void generatePawnMovesFrom(Position position) {
    generateUpperMovesFrom(position, generatePawnMovesInDirection);
}

void generatePawnMovesInDirection(Position from, Position direction) {
    Position to = {from.row + direction.row, from.col + direction.col};
    if (isOnBoard(to) && isEmpty(board, to)) {
        Move move;
        fillNonCaptureMove(&move, from, to);
        addMoveToPlayerMoves(move);
    }
}

