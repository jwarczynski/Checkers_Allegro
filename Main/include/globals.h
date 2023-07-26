//
// Created by Jj on 26/07/2023.
//

#ifndef CHECKERS_GLOBALS_H
#define CHECKERS_GLOBALS_H

#include "types.h"
#include "allegro5/threads.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

extern ALLEGRO_MUTEX* clickMutex;
extern ALLEGRO_COND* clickCond;

extern ALLEGRO_MUTEX *moveExecutedMutex;
extern ALLEGRO_COND *moveExecutedCond;

#endif //CHECKERS_GLOBALS_H
