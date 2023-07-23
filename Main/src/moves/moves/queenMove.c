//
// Created by Jj on 15/07/2023.
//

#include "moves/moves/queenMove.h"
#include "moves/moveUtil.h"
#include "moves/move.h"

#define MAX_QUEEN_MOVES 13

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void generateQueenMovesFrom(Position position) {
    initQueenMovesFrom(position);
    generateAllDirectionsMovesFrom(position, generateQueenMovesInDirection);
    if (playerMoves.pieceMoves[playerMoves.pieceMovesSize].size > 0) {
        playerMoves.pieceMovesSize++;
    }
}

void initQueenMovesFrom(Position position) {
    initPieceMovesFrom(position, MAX_QUEEN_MOVES);
}

void generateQueenMovesInDirection(Position position, Position direction) {
    while (isOnBoard(position) && isEmpty(board, position)) {
        addPieceMove(position);
        changePosition(&position, direction.row, direction.col);
    }
}
