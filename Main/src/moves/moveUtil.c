//
// Created by Jj on 08/07/2023.
//

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "moves/moveUtil.h"
#include "globals.h"


bool isWhitePiece(Piece piece) {
    return piece == WHITE_PAWN || piece == WHITE_QUEEN;
}

bool isBlackPiece(Piece piece) {
    return piece == BLACK_PAWN || piece == BLACK_QUEEN;
}

bool isOnBoard(Position position) {
    return position.row >= 0 && position.row < BOARD_SIZE && position.col >= 0 && position.col < BOARD_SIZE;
}

bool isQueen(Piece piece) {
    return piece == WHITE_QUEEN || piece == BLACK_QUEEN;
}

bool isPawn(Piece piece) {
    return piece == WHITE_PAWN || piece == BLACK_PAWN;
}

bool isCurrentPlayerPiece(Piece piece) {
    return (currentPlayer == WHITE && isWhitePiece(piece)) || (currentPlayer == BLACK && isBlackPiece(piece));
}

bool isOpponentPiece(Piece piece) {
    return (currentPlayer == WHITE && isBlackPiece(piece)) || (currentPlayer == BLACK && isWhitePiece(piece));
}

bool isOutOfBounds(Position position) {
    return !isOnBoard(position);
}

bool isEmpty(Piece board[8][8], Position position) {
    return board[position.row][position.col] == EMPTY;
}

void changePosition(Position *position, int row, int col) {
    position->row += row;
    position->col += col;
}

Position getEmptyPosition() {
    return (Position) {-1, -1};
}

Move *copyMove(Move move) {
    Move *copy = malloc(sizeof(Move));

    PositionPath *positionPathCopy = copyPositionPath(move.positionPath);
    CaptureCollection *captureCopy = copyCapture(move.captureCollection);

    copy->positionPath = *positionPathCopy;
    copy->captureCollection = *captureCopy;

    return copy;
}

PositionPath *copyPositionPath(PositionPath positionPath) {
    PositionPath *copy = malloc(sizeof(PositionPath));
    copy->path = malloc(sizeof(Position) * positionPath.allocatedSize);
    memcpy(copy->path, positionPath.path, sizeof(Position) * positionPath.size);
    copy->size = positionPath.size;
    copy->allocatedSize = positionPath.allocatedSize;
    return copy;
}

CaptureCollection *copyCapture(CaptureCollection capture) {
    CaptureCollection *copy = malloc(sizeof(CaptureCollection));
    copy->captures = malloc(sizeof(Position) * capture.allocatedSize);
    memcpy(copy->captures, capture.captures, sizeof(Position) * capture.allocatedSize);
    copy->size = capture.size;
    copy->allocatedSize = capture.allocatedSize;
    return copy;
}

void initPlayerMoves() {
    playerMoveCollection.moves = (Move *) malloc(sizeof(Move) * INITIAL_PLAYER_MOVES_CAPACITY);
    playerMoveCollection.allocatedSize = INITIAL_PLAYER_MOVES_CAPACITY;
    playerMoveCollection.size = 0;
    markAllMovesUnInitialized();
}

Move *getStartingMove(Position startingPosition) {
    Move *move = malloc(sizeof(Move));

    move->positionPath.path = malloc(sizeof(Position) * INITIAL_PATH_SIZE);
    move->positionPath.path[0] = startingPosition;
    move->positionPath.size = 1;
    move->positionPath.allocatedSize = INITIAL_PATH_SIZE;

    move->captureCollection.size = 0;
    move->captureCollection.allocatedSize = 0;
    move->captureCollection.captures = NULL;

    return move;
}

void markAllMovesUnInitialized() {
    for (int i = 0; i < INITIAL_PLAYER_MOVES_CAPACITY; i++) {
        playerMoveCollection.moves[i].captureCollection.captures = NULL;
        playerMoveCollection.moves[i].captureCollection.size = 0;
        playerMoveCollection.moves[i].captureCollection.allocatedSize = 0;

        playerMoveCollection.moves[i].positionPath.path = NULL;
        playerMoveCollection.moves[i].positionPath.size = 0;
        playerMoveCollection.moves[i].positionPath.allocatedSize = 0;
    }
}

void initMoveIfNull(Move **intermediateMoves) {
    if (*intermediateMoves == NULL) {
        *intermediateMoves = (Move *) malloc(sizeof(Move));

        (*intermediateMoves)->positionPath.path = (Position*)malloc(sizeof(Position) * INITIAL_PATH_SIZE);
        (*intermediateMoves)->positionPath.allocatedSize = INITIAL_PATH_SIZE;
        (*intermediateMoves)->positionPath.size = 0;

        (*intermediateMoves)->captureCollection.captures = (Position*)malloc(sizeof(Position) * INITIAL_CAPTURES_CAPACITY);
        (*intermediateMoves)->captureCollection.allocatedSize = INITIAL_CAPTURES_CAPACITY;
        (*intermediateMoves)->captureCollection.size = 0;
    }

    if ((*intermediateMoves)->positionPath.path == NULL) {
        (*intermediateMoves)->positionPath.path = (Position*)malloc(sizeof(Position) * INITIAL_PATH_SIZE);
        (*intermediateMoves)->positionPath.allocatedSize = INITIAL_PATH_SIZE;
        (*intermediateMoves)->positionPath.size = 0;
    }

    if ((*intermediateMoves)->captureCollection.captures == NULL) {
        (*intermediateMoves)->captureCollection.captures = (Position*)malloc(sizeof(Position) * INITIAL_CAPTURES_CAPACITY);
        (*intermediateMoves)->captureCollection.allocatedSize = INITIAL_CAPTURES_CAPACITY;
        (*intermediateMoves)->captureCollection.size = 0;
    }
}


void destroyPlayerMoves() {
    setbuf(stdout, 0);
    for (int i = 0; i < playerMoveCollection.size; i++) {
        free(playerMoveCollection.moves[i].captureCollection.captures);
        free(playerMoveCollection.moves[i].positionPath.path);
    }
    free(playerMoveCollection.moves);
}