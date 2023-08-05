//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_MOVE_UTIL_H
#define CHECKERS_MOVE_UTIL_H

#include <stdbool.h>
#include "types.h"

bool isWhitePiece(Piece piece);
bool isBlackPiece(Piece piece);
bool isOnBoard(Position position);
bool isQueen(Piece piece);
bool isPawn(Piece piece);
bool isCurrentPlayerPiece(Piece piece);
bool isOpponentPiece(Piece piece);
bool isOutOfBounds(Position position);
bool isEmpty(Piece board[8][8], Position position);
void changePosition(Position *position, int row, int col);
Position getEmptyPosition();
CaptureCollection *copyCapture(CaptureCollection capture);

void initPlayerMoves();
Move *getStartingMove(Position startingPosition);
void markAllMovesUnInitialized();
void initMoveIfNull(Move **intermediateMoves);
Move *copyMove(Move move);
PositionPath *copyPositionPath(PositionPath positionPath);

void destroyPlayerMoves();


#endif //CHECKERS_MOVE_UTIL_H
