//
// Created by Jj on 21/07/2023.
//

#include <stdbool.h>
#include "gameEngine/moveValidator.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

bool checkMoveValidity(PlayerMoves playerChoice) {
    if (playerMoves.queenCaptureMovesSize > 0) {
        return checkQueenCaptureMoveValidity(playerChoice.queenCaptureMoves[0]);
    }

    if (playerMoves.pawnCaptureMovesSize > 0) {
        return checkPawnCaptureMovesValidity(playerChoice.pawnCaptureMoves[0]);
    }

    return checkPieceMoveValidity(playerChoice.pieceMoves[0]);
}

bool checkQueenCaptureMoveValidity(PieceCaptureMoves playerChoice) {
    if (playerChoice.captureCollections[0].captureSize <  findMaxCapturesQueenMoveSize()){
        return false;
    }
    return checkCaptureMovesValidity(playerChoice, playerMoves.queenCaptureMoves, playerMoves.queenCaptureMovesSize);
}

bool checkPawnCaptureMovesValidity(PieceCaptureMoves playerChoice) {
    if (playerChoice.captureCollections[0].captureSize <  findMaxCapturesPawnMoveSize()){
        return false;
    }
    checkCaptureMovesValidity(playerChoice, playerMoves.pawnCaptureMoves, playerMoves.pawnCaptureMovesSize);
}

bool checkCaptureMovesValidity(PieceCaptureMoves playerChoice, PieceCaptureMoves *validMoves, int validMovesSize) {
    for (int i = 0; i < validMovesSize; ++i) {
        if (validCaptureMovesContains(playerChoice, validMoves[i])) {
            return true;
        }
    }
    return false;
}

bool validCaptureMovesContains(PieceCaptureMoves playerChoice, PieceCaptureMoves validCaptureMoves) {
    for (int i = 0; i < validCaptureMoves.size; ++i) {
        if (areCaptureMovesEqual(validCaptureMoves.toArray[i], playerChoice.toArray[0], validCaptureMoves.captureCollections[i], playerChoice.captureCollections[0])) {
            return true;
        }
    }
    return false;
}

bool areCaptureMovesEqual(Position to1, Position to2, CaptureCollection captureCollection1, CaptureCollection captureCollection2) {
    return arePointsEqual(to1, to2) && areCaptureCollectionsEqual(captureCollection1, captureCollection2);
}

bool arePointsEqual(Position point1, Position point2) {
    return point1.row == point2.row && point1.col == point2.col;
}

bool areCaptureCollectionsEqual(CaptureCollection captureCollection1, CaptureCollection captureCollection2) {
    if (captureCollection1.captureSize != captureCollection2.captureSize) {
        return false;
    }
    return areCapturesEqual(captureCollection1.captures, captureCollection2.captures, captureCollection1.captureSize);
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

bool checkPieceMoveValidity(PieceMoves playerChoice) {
    for (int i = 0; i < playerMoves.pieceMovesSize; ++i) {
        if (validPieceMoveContains(playerChoice, playerMoves.pieceMoves[i])) {
            return true;
        }
    }
    return false;
}

bool validPieceMoveContains(PieceMoves playerChoice, PieceMoves validMove) {
    for (int i = 0 ; i < validMove.size; ++i) {
        if (arePointsEqual(playerChoice.to[0], validMove.to[i]) && arePointsEqual(playerChoice.from, validMove.from)) {
            return true;
        }
    }
    return false;
}

int findMaxCapturesQueenMoveSize() {
   return findMaxCapturesMoveSize(playerMoves.queenCaptureMoves, playerMoves.queenCaptureMovesSize);
}

int findMaxCapturesPawnMoveSize() {
   return findMaxCapturesMoveSize(playerMoves.pawnCaptureMoves, playerMoves.pawnCaptureMovesSize);
}

int findMaxCapturesQueenMoveSizeForPiece(PieceCaptureMoves captureMove) {
    int maxCaptures = 0;
    for (int i = 0; i < captureMove.size; ++i) {
        if (captureMove.captureCollections[i].captureSize > maxCaptures) {
            maxCaptures = captureMove.captureCollections[i].captureSize;
        }
    }
    return maxCaptures;
}

int findMaxCapturesMoveSize(PieceCaptureMoves *validMoves, int validMovesSize) {
    int maxCaptures = 0;
    for (int i = 0; i < validMovesSize; ++i) {
        int maxCapturesForIthPiece = findMaxCapturesQueenMoveSizeForPiece(validMoves[i]);
        if (maxCapturesForIthPiece > maxCaptures) {
            maxCaptures = maxCapturesForIthPiece;
        }
    }
    return maxCaptures;
}