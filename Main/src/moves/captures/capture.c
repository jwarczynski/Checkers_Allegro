//
// Created by Jj on 16/07/2023.
//

#include <stdbool.h>
#include <stdio.h>

#include "moves/captures/capture.h"
#include "moves/captures/queenCapture.h"
#include "moves/captures/pawnCapture.h"
#include "globals.h"


bool addCaptureMoves(Move *intermediateMoves, Position position, Position direction, PieceType pieceType) {
    switch (pieceType) {
        case PAWN:
            return addPawnCaptureMoves(intermediateMoves, position, direction);
        case QUEEN:
            return addQueenCaptureMoves(intermediateMoves, position, direction);
        default:
            printf("Invalid piece type");
            return false;
    }
}

bool addUpperLeftCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType) {
    Position direction = {1, -1};
    return addCaptureMoves(intermediateMoves, position, direction, pieceType);
}

bool addUpperRightCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType) {
    Position direction = {1, 1};
    return addCaptureMoves(intermediateMoves, position, direction, pieceType);
}

bool addLowerLeftCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType) {
    Position direction = {-1, -1};
    return addCaptureMoves(intermediateMoves, position, direction, pieceType);
}

bool addLowerRightCaptureMoves(Move *intermediateMoves, Position position, PieceType pieceType) {
    Position direction = {-1, 1};
    return addCaptureMoves(intermediateMoves, position, direction, pieceType);
}

bool tryAllDirectionsForCapture(Move *intermediateMoves, Position position, PieceType pieceType) {
// each function has to be executed even if the previous one returns true ,so it cannot be simplified with &&
    bool upperLeftCapturePossible = addUpperLeftCaptureMoves(intermediateMoves, position, pieceType);
    bool upperRightCapturePossible = addUpperRightCaptureMoves(intermediateMoves, position, pieceType);
    bool lowerLeftCapturePossible = addLowerLeftCaptureMoves(intermediateMoves, position, pieceType);
    bool lowerRightCapturePossible = addLowerRightCaptureMoves(intermediateMoves, position, pieceType);

    return !upperLeftCapturePossible && !upperRightCapturePossible &&
           !lowerLeftCapturePossible && !lowerRightCapturePossible;
}

bool addNextCaptureMoveIfPossible(Move *intermediateMoves, Position position, PieceType pieceType) {
    bool noCapturesPossible = tryAllDirectionsForCapture(intermediateMoves, position, pieceType);

    if (noCapturesPossible) {
        savePositionAndCaptures(intermediateMoves);
    } else {
        freeMovesUtterly(intermediateMoves);
    }
    return true;
}

void savePositionAndCaptures(Move *intermediateMoves) {
    Move *move = &(playerMoveCollection.moves[playerMoveCollection.size]);
    if (hasMoreOrEqualCapturesAsPreviousMove(intermediateMoves)) {
        move->positionPath = intermediateMoves->positionPath;
        move->captureCollection = intermediateMoves->captureCollection;

        playerMoveCollection.size++;
        return freeMoves(intermediateMoves);
    }
    freeMovesUtterly(intermediateMoves);

}

bool hasMoreOrEqualCapturesAsPreviousMove(Move *intermediateMoves) {
    if (playerMoveCollection.size == 0) {
        return true;
    }
    for (int i = 0; i < playerMoveCollection.size; ++i) {
        Move *previousMove = &(playerMoveCollection.moves[i]);
        if (intermediateMoves->captureCollection.size < previousMove->captureCollection.size) {
            return false;
        }
    }
    return true;
}

void freeMovesUtterly(Move *intermediateMoves) {
    free(intermediateMoves->positionPath.path);
    free(intermediateMoves->captureCollection.captures);
    freeMoves(intermediateMoves);
}

void freeMoves(Move *intermediateMoves) {
    free(intermediateMoves);
    intermediateMoves = NULL;
}

