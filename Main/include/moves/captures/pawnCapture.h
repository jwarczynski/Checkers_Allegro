//
// Created by Jj on 15/07/2023.
//

#ifndef CHECKERS_PAWN_CAPTURE_H
#define CHECKERS_PAWN_CAPTURE_H

#include "types.h"

void generatePawnCaptureMovesFrom(Position position);
bool tryAllDirectionsForPawnCapture(CaptureCollection *previousCaptures, Position position);
bool addPawnCaptureMovesIfEmpty(CaptureCollection *previousCaptures, Position capturedPiecePosition, Position direction);
bool addNextPawnCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position);
bool addPawnCaptureMoves(CaptureCollection *previousCaptures, Position position, Position direction);
void initPawnCaptureMovesFrom(Position position);
void savePawnPositionAndCapture(CaptureCollection *captureCollection, Position position);

#endif //CHECKERS_PAWN_CAPTURE_H
