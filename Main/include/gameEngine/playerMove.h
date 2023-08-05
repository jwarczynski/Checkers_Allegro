//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_PLAYER_MOVE_H
#define CHECKERS_PLAYER_MOVE_H

#include <stdbool.h>
#include "types.h"

void generatePlayerMoves();
void initPlayerMoves();
PlayerMoves getEmptyPlayerMoves();


bool generatePawnCaptureMoves();
bool generateQueenCaptureMoves();
bool generatePawnCapturesIfPlayerPawn(Position position);
bool generateQueenCapturesIfPlayerQueen(Position position);

void generateNoCaptureMoves();
void generateNoCaptureMovesByType(Position position);

bool performMoveOperationForEachSquare(bool (*operation)(Position));


void generateMoves();


#endif //CHECKERS_PLAYER_MOVE_H
