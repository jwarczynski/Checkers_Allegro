//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

#include "types.h"

void addPieceMove(Position position);
void addMoveToPlayerMoves(Move move);
void fillNonCaptureMove(Move *move, Position from, Position to);
void addNonCaptureMovePositionPath(Move *move, Position from, Position to);
void markMoveCapturesEmpty(Move *move);
void reallocatePieceMovesMemoryIfOverflow();

void generateUpperMovesFrom(Position position, PieceMoveStrategy strategy);
void generateAllDirectionsMovesFrom(Position position, PieceMoveStrategy strategy);
void generateUpperLeftMoves(Position position, PieceMoveStrategy strategy);
void generateUpperRightMoves(Position position, PieceMoveStrategy strategy);
void generateLowerLeftMoves(Position position, PieceMoveStrategy strategy);
void generateLowerRightMoves(Position position, PieceMoveStrategy strategy);

void generateMovesInDirection(Position position, Position direction, PieceMoveStrategy strategy);

#endif //CHECKERS_MOVE_H
