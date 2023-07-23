//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_PLAYER_MOVE_H
#define CHECKERS_PLAYER_MOVE_H

#include "types.h"

void generatePlayerMoves();
void generateMovesByType(Position position);
void initPlayerMoves();
void deallocatePlayerMovesMemory();
PlayerMoves getEmptyPlayerMoves();


#endif //CHECKERS_PLAYER_MOVE_H
