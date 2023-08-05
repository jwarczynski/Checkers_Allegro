//
// Created by Jj on 15/07/2023.
//

#ifndef CHECKERS_PAWN_CAPTURE_H
#define CHECKERS_PAWN_CAPTURE_H

#include "types.h"

bool generatePawnCaptureMovesFrom(Position position);
bool tryAllDirectionsForPawnCapture(Move *intermediateMoves, Position position);
bool addPawnCaptureMovesIfEmpty(Move *intermediateMoves, Position capturedPiecePosition, Position direction);
bool addNextPawnCaptureMoveIfPossible(Move *intermediateMoves, Position position);
bool addPawnCaptureMoves(Move *intermediateMoves, Position position, Position direction);
void initPawnCaptureMovesFrom(Position position);
void savePawnPositionAndCapture(Move *intermediateMoves, Position position);

#endif //CHECKERS_PAWN_CAPTURE_H
