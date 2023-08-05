//
// Created by Jj on 16/07/2023.
//

#ifndef CHECKERS_CAPTURE_H
#define CHECKERS_CAPTURE_H

#include "types.h"

bool tryAllDirectionsForCapture(Move *intermediateMoves, Position position, PieceType pieceType);
void markAllCaptureCollectionsAsNotInitialized(CaptureCollection *captureCollectionArray, int start, int end);

bool addNextCaptureMoveIfPossible(Move *intermediateMoves, Position position, PieceType pieceType);
void savePositionAndCaptures(Move *move);
bool hasMoreOrEqualCapturesAsPreviousMove(Move *intermediateMoves);

void freeMovesUtterly(Move *intermediateMoves);
void freeMoves(Move *intermediateMoves);

bool addUpperLeftCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType);
bool addUpperRightCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType);
bool addLowerLeftCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType);
bool addLowerRightCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType);

#endif //CHECKERS_CAPTURE_H
