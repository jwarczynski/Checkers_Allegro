//
// Created by Jj on 15/07/2023.
//

#ifndef CHECKERS_QUEEN_MOVE_H
#define CHECKERS_QUEEN_MOVE_H

#include "types.h"

void generateQueenMovesFrom(Position position);
void generateQueenMovesInDirection(Position position, Position direction);
void initQueenMovesFrom(Position position);

#endif //CHECKERS_QUEEN_MOVE_H
