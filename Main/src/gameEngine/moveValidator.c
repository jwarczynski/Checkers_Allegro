//
// Created by Jj on 21/07/2023.
//

#include <stdbool.h>
#include "gameEngine/moveValidator.h"
#include "globals.h"


bool isMoveValid(Move move) {
    for (int i = 0; i < playerMoveCollection.size; ++i) {
        if (areMovesEqual(move, playerMoveCollection.moves[i])) {
            return true;
        }
    }
    return false;
}

bool areMovesEqual(Move move1, Move move2) {
    return arePositionPathsEqual(move1.positionPath, move2.positionPath) &&
           areCaptureCollectionsEqual(move1.captureCollection, move2.captureCollection);
}

bool arePositionPathsEqual(PositionPath positionPath1, PositionPath positionPath2) {
    if (positionPath1.size != positionPath2.size) {
        return false;
    }
    for (int i = 0; i < positionPath1.size; ++i) {
        if (arePointsDifferent(positionPath1.path[i], positionPath2.path[i])) {
            return false;
        }
    }
    return true;
}

bool arePointsEqual(Position point1, Position point2) {
    return point1.row == point2.row && point1.col == point2.col;
}

bool areCaptureCollectionsEqual(CaptureCollection captureCollection1, CaptureCollection captureCollection2) {
    if (captureCollection1.size != captureCollection2.size) {
        return false;
    }
    return areCapturesEqual(captureCollection1.captures, captureCollection2.captures, captureCollection1.size);
}

bool areCapturesEqual(Position *captures1, Position *captures2, int size) {
    for (int i = 0; i < size; ++i) {
        if (arePointsDifferent(captures1[i], captures2[i])) {
            return false;
        }
    }
    return true;
}

bool arePointsDifferent(Position point1, Position point2) {
    return !arePointsEqual(point1, point2);
}

bool isNotNullPosition(Position position) {
    return arePointsDifferent(position, getNullPosition());
}

Position getNullPosition() {
    Position nullPosition;
    nullPosition.row = -1;
    nullPosition.col = -1;
    return nullPosition;
}