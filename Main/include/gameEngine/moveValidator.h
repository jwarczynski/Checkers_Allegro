//
// Created by Jj on 21/07/2023.
//

#ifndef CHECKERS_MOVE_VALIDATOR_H
#define CHECKERS_MOVE_VALIDATOR_H

#include "types.h"

// INTERFACE
bool isMoveValid(Move move);

// IMPLEMENTATION
bool areMovesEqual(Move move1, Move move2);
bool arePositionPathsEqual(PositionPath positionPath1, PositionPath positionPath2);
bool areCaptureCollectionsEqual(CaptureCollection captureCollection1, CaptureCollection captureCollection2);
bool areCapturesEqual(Position *captures1, Position *captures2, int size);
bool arePointsEqual(Position point1, Position point2);
bool arePointsDifferent(Position point1, Position point2);

Position getNullPosition();
bool isNotNullPosition(Position position);


#endif //CHECKERS_MOVE_VALIDATOR_H
