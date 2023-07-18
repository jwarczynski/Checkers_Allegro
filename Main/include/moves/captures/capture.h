//
// Created by Jj on 16/07/2023.
//

#ifndef CHECKERS_CAPTURE_H
#define CHECKERS_CAPTURE_H

#include "types.h"

bool tryAllDirectionsForCapture(CaptureCollection *previousCaptures, Position position, PieceType pieceType);
bool addNextCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position, PieceType pieceType);
void markAllCaptureCollectionsAsNotInitialized(CaptureCollection *captureCollectionArray, int start, int end);
void savePositionAndCaptures(CaptureCollection *previousCaptures, Position position, PieceType pieceType);

#endif //CHECKERS_CAPTURE_H
