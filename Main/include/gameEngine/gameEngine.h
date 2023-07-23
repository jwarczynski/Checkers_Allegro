//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_GAME_ENGINE_H
#define CHECKERS_GAME_ENGINE_H

#include "types.h"

void runGame();
void runTurn();
void changePlayer();
void executeMove(PlayerMoves playerMove);
void executeCaptureMove(PieceCaptureMoves pieceCaptureMoves);
void executeNonCaptureMove(PieceMoves pieceMove);

void removeCapturedPieces(CaptureCollection captureCollection);
void moveFromTo(Position from, Position to);

void upgradePawnIfReachedMorphSquare(Position position);

#endif //CHECKERS_GAME_ENGINE_H
