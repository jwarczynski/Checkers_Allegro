//
// Created by Jj on 07/07/2023.
//

#include <malloc.h>

#include "moves/move.h"
#include "moves/moveUtil.h"
#include "globals.h"


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
    strategy(position, direction);
}

void addPieceMove(Position position) {
    Move *move = &playerMoveCollection.moves[playerMoveCollection.size];
    initMoveIfNull(&move);
    move->positionPath.path[move->positionPath.size++] = position;

    playerMoveCollection.size++;
}


void fillNonCaptureMove(Move *move, Position from, Position to) {
    addNonCaptureMovePositionPath(move, from, to);
    markMoveCapturesEmpty(move);
}

void addNonCaptureMovePositionPath(Move *move, Position from, Position to) {
    move->positionPath.path = malloc(sizeof(Position) * 2);
    move->positionPath.size = 2;
    move->positionPath.allocatedSize = 2;
    move->positionPath.path[0] = from;
    move->positionPath.path[1] = to;
}

void markMoveCapturesEmpty(Move *move) {
    move->captureCollection.captures = NULL;
    move->captureCollection.size = 0;
    move->captureCollection.allocatedSize = 0;
}

void addMoveToPlayerMoves(Move move) {
    playerMoveCollection.moves[playerMoveCollection.size++] = move;
}