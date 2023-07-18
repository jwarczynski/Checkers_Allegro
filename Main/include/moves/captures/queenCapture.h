//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_QUEEN_CAPTURE_H
#define CHECKERS_QUEEN_CAPTURE_H

#include <stdbool.h>

void generateQueenCaptureMovesFrom(Position position);

void initQueenCaptureMovesFrom(Position position);
void markAllCaptureCollectionsAsNotInitialized(CaptureCollection *captureCollectionArray, int start, int end);

void reallocateQueenCaptureMoves(PieceCaptureMoves *queenCaptureMoves);
void deallocateCaptureMoves(PieceCaptureMoves *pieceCaptureMoves);

bool tryAllDirectionsForQueenCapture(CaptureCollection *previousCaptures, Position position);

bool addUpperLeftQueenCaptureMoves(CaptureCollection *previousCaptures, Position position);
bool addUpperRightQueenCaptureMoves(CaptureCollection *previousCaptures, Position position);
bool addLowerLeftQueenCaptureMoves(CaptureCollection *previousCaptures, Position position);
bool addLowerRightQueenCaptureMoves(CaptureCollection *previousCaptures, Position position);

bool addQueenCaptureMoves(CaptureCollection *previousCaptures, Position position, Position direction);
bool addQueenCaptureMovesIfEmpty(CaptureCollection *previousCaptures, Position capturedPiecePosition, Position direction);
bool addNextQueenCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position);

void saveQueenPositionAndCaptures(CaptureCollection *captureCollection, Position position);

#endif //CHECKERS_QUEEN_CAPTURE_H
