//
// Created by Jj on 10/07/2023.
//

#ifndef CHECKERS_CAPTURE_UTIL_H
#define CHECKERS_CAPTURE_UTIL_H

#include "types.h"

bool isAlreadyCaptured(CaptureCollection previousCaptures, Position position);
void initCaptureIfNull(CaptureCollection *captures, PieceType pieceType);
void addCaptureToCaptureArray(CaptureCollection *captures, Position capturedPiecePosition);
bool isCaptureForbidden(Position position, CaptureCollection captureCollection);
void addIntermediateMove(Move *intermediateMoves, Position to, Position capturePosition);

#endif //CHECKERS_CAPTURE_UTIL_H

