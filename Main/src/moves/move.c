//
// Created by Jj on 07/07/2023.
//

#include <malloc.h>

#include "moves/move.h"
#include "moves/moveUtil.h"


extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void initPieceMovesFrom(Position position, int initialSize) {
    reallocatePieceMovesMemoryIfOverflow();
    playerMoves.pieceMoves[playerMoves.pieceMovesSize].size = 0;
    playerMoves.pieceMoves[playerMoves.pieceMovesSize].from = position;
    playerMoves.pieceMoves[playerMoves.pieceMovesSize].to = malloc(sizeof(Position) * initialSize);
    playerMoves.pieceMoves[playerMoves.pieceMovesSize].allocatedSize = initialSize;
}

void reallocatePieceMovesMemoryIfOverflow() {
    if (playerMoves.pieceMovesSize == playerMoves.pieceMovesAllocatedSize) {
        playerMoves.pieceMovesAllocatedSize *= 2;
        playerMoves.pieceMoves = realloc(playerMoves.pieceMoves, sizeof(PieceMoves) * playerMoves.pieceMovesAllocatedSize);
    }
}

void generateUpperMovesFrom(Position position, PieceMoveStrategy strategy) {
    generateUpperLeftMoves(position, strategy);
    generateUpperRightMoves(position, strategy);
}

void generateAllDirectionsMovesFrom(Position position, PieceMoveStrategy strategy) {
    generateUpperMovesFrom(position, strategy);
    generateLowerLeftMoves(position, strategy);
    generateLowerRightMoves(position, strategy);
}

void generateUpperLeftMoves(Position position, PieceMoveStrategy strategy) {
    Position direction;
    direction.row = currentPlayer == WHITE ? 1 : -1;
    direction.col = -1;
    generateMovesInDirection(position, direction, strategy);
}

void generateUpperRightMoves(Position position, PieceMoveStrategy strategy) {
    Position direction;
    direction.row = currentPlayer == WHITE ? 1 : -1;
    direction.col = 1;
    generateMovesInDirection(position, direction, strategy);
}

void generateLowerLeftMoves(Position position, PieceMoveStrategy strategy) {
    Position direction;
    direction.row = currentPlayer == WHITE ? -1 : 1;
    direction.col = -1;
    generateMovesInDirection(position, direction, strategy);
}

void generateLowerRightMoves(Position position, PieceMoveStrategy strategy) {
    Position direction;
    direction.row = currentPlayer == WHITE ? -1 : 1;
    direction.col = 1;
    generateMovesInDirection(position, direction, strategy);
}

void generateMovesInDirection(Position position, Position direction, PieceMoveStrategy strategy) {
    changePosition(&position, direction.row, direction.col);
    strategy(position, direction);
}

void addPieceMove(Position position) {
    PieceMoves *currentMove = &(playerMoves.pieceMoves[playerMoves.pieceMovesSize]);
//    currentMove->from = position;
    currentMove->to[currentMove->size] = position;
    currentMove->size++;
//    playerMoves.pieceMovesSize++;
}
