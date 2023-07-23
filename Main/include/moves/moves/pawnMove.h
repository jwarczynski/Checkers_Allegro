//
// Created by Jj on 15/07/2023.
//

#ifndef CHECKERS_PAWN_MOVE_H
#define CHECKERS_PAWN_MOVE_H

#include "types.h"

void generatePawnMovesFrom(Position position);
void generatePawnMovesInDirection(Position position, Position direction);
void initPawnMovesFrom(Position position);

#endif //CHECKERS_PAWN_MOVE_H
