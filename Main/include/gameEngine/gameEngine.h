//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_GAME_ENGINE_H
#define CHECKERS_GAME_ENGINE_H

#include "types.h"

void runGame();
void runTurn();
void waitForUserChoice();
void changePlayer();
void executeMove(Move move);
void executeIntermediateMove(Position from, Position to, Position capture);
void executeLastIntermediateMove(Position from, Position to, Position capture);


void removeCapturedPieces(CaptureCollection captureCollection);
void moveFromTo(Position from, Position to);

void upgradePawnIfReachedMorphSquare(Position position);
void resetUserMoveChoice();
void unlockUserInputThread();

#endif //CHECKERS_GAME_ENGINE_H
