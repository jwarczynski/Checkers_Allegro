//
// Created by Jj on 16/07/2023.
//

#include <stdbool.h>
#include <stdio.h>

#include "moves/captures/capture.h"
#include "moves/captures/queenCapture.h"
#include "moves/captures/pawnCapture.h"

extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

bool addCaptureMoves(CaptureCollection *previousCaptures, Position position, Position direction, PieceType pieceType) {
    switch (pieceType) {
        case PAWN:
            return addPawnCaptureMoves(previousCaptures, position, direction);
        case QUEEN:
            return addQueenCaptureMoves(previousCaptures, position, direction);
        default:
            printf("Invalid piece type");
            return false;
    }
}

bool addUpperLeftCaptureMoves(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    Position direction = {1, -1};
    return addCaptureMoves(previousCaptures, position, direction, pieceType);
}

bool addUpperRightCaptureMoves(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    Position direction = {1, 1};
    return addCaptureMoves(previousCaptures, position, direction, pieceType);
}

bool addLowerLeftCaptureMoves(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    Position direction = {-1, -1};
    return addCaptureMoves(previousCaptures, position, direction, pieceType);
}

bool addLowerRightCaptureMoves(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    Position direction = {-1, 1};
    return addCaptureMoves(previousCaptures, position, direction, pieceType);
}

bool tryAllDirectionsForCapture(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
// each function has to be executed even if the previous one returns true ,so it cannot be simplified with &&
    bool upperLeftCapturePossible = addUpperLeftCaptureMoves(previousCaptures, position, pieceType);
    bool upperRightCapturePossible = addUpperRightCaptureMoves(previousCaptures, position, pieceType);
    bool lowerLeftCapturePossible = addLowerLeftCaptureMoves(previousCaptures, position, pieceType);
    bool lowerRightCapturePossible = addLowerRightCaptureMoves(previousCaptures, position, pieceType);

    return !upperLeftCapturePossible && !upperRightCapturePossible &&
           !lowerLeftCapturePossible &&!lowerRightCapturePossible;
}

bool addNextCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    bool noCapturesPossible = tryAllDirectionsForCapture(previousCaptures, position, pieceType);

    if (noCapturesPossible) {
        savePositionAndCaptures(previousCaptures, position, pieceType);
        return false;
    }
    return true;
}

void markAllCaptureCollectionsAsNotInitialized(CaptureCollection *captureCollectionArray, int start, int end) {
    for (int i = start; i < end; ++i) {
        captureCollectionArray[i].captures = NULL;
        captureCollectionArray[i].captureSize = 0;
        captureCollectionArray[i].captureAllocatedSize = 0;
    }
}

void savePositionAndCaptures(CaptureCollection *previousCaptures, Position position, PieceType pieceType) {
    if (pieceType == QUEEN) {
        saveQueenPositionAndCaptures(previousCaptures, position);
    } else {
        savePawnPositionAndCapture(previousCaptures, position);
    }
}