//
// Created by Jj on 15/07/2023.
//


#include "types.h"
#include "moves/moveUtil.h"
#include "moves/moves/pawnMove.h"
#include "moves/move.h"


#define MAX_PAWN_MOVES 2

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


void generatePawnMovesFrom(Position position) {
    initPawnMovesFrom(position);
    generateUpperMovesFrom(position, generatePawnMovesInDirection);
    if (playerMoves.pieceMoves[playerMoves.pieceMovesSize].size > 0) {
        playerMoves.pieceMovesSize++;
    }
}

void initPawnMovesFrom(Position position) {
    initPieceMovesFrom(position, MAX_PAWN_MOVES);
}

void generatePawnMovesInDirection(Position position, Position direction) {
    if (isOnBoard(position) && isEmpty(board, position)) {
        addPieceMove(position);
    }
}
