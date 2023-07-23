//
// Created by Jj on 21/07/2023.
//

#ifndef CHECKERS_MOVE_VALIDATOR_H
#define CHECKERS_MOVE_VALIDATOR_H

#include "types.h"

bool checkMoveValidity(PlayerMoves playerChoice);

bool checkQueenCaptureMoveValidity(PieceCaptureMoves queenCaptureMove);
bool checkPawnCaptureMovesValidity(PieceCaptureMoves playerChoice);
bool checkCaptureMovesValidity(PieceCaptureMoves playerChoice, PieceCaptureMoves *validMoves, int validMovesSize);

bool checkPieceMoveValidity(PieceMoves playerChoice);

bool validCaptureMovesContains(PieceCaptureMoves playerChoice, PieceCaptureMoves validCaptureMoves);
bool areCaptureMovesEqual(Position to1, Position to2, CaptureCollection captureCollection1, CaptureCollection captureCollection2);
bool arePointsEqual(Position point1, Position point2);
bool arePointsDifferent(Position point1, Position point2);
bool areCaptureCollectionsEqual(CaptureCollection captureCollection1, CaptureCollection captureCollection2);
bool areCapturesEqual(Position *captures1, Position *captures2, int size);

bool validPieceMoveContains(PieceMoves playerChoice, PieceMoves validMove);

int findMaxCapturesQueenMoveSize();
int findMaxCapturesPawnMoveSize();
int findMaxCapturesMoveSize(PieceCaptureMoves *validMoves, int validMovesSize);
int findMaxCapturesQueenMoveSizeForPiece(PieceCaptureMoves captureMove);


#endif //CHECKERS_MOVE_VALIDATOR_H
