//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

#include "types.h"

void initPieceMovesFrom(Position position, int initialSize);
void addPieceMove(Position position);
void reallocatePieceMovesMemoryIfOverflow();

void generateUpperMovesFrom(Position position, PieceMoveStrategy strategy);
void generateAllDirectionsMovesFrom(Position position, PieceMoveStrategy strategy);
void generateUpperLeftMoves(Position position, PieceMoveStrategy strategy);
void generateUpperRightMoves(Position position, PieceMoveStrategy strategy);
void generateLowerLeftMoves(Position position, PieceMoveStrategy strategy);
void generateLowerRightMoves(Position position, PieceMoveStrategy strategy);

void generateMovesInDirection(Position position, Position direction, PieceMoveStrategy strategy);

#endif //CHECKERS_MOVE_H
