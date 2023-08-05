//
// Created by Jj on 08/07/2023.
//

#ifndef CHECKERS_QUEEN_CAPTURE_H
#define CHECKERS_QUEEN_CAPTURE_H

#include <stdbool.h>

bool generateQueenCaptureMovesFrom(Position position);
bool tryAllDirectionsForQueenCapture(Move *move, Position position);
bool addQueenCaptureMoves(Move *intermediateMoves, Position position, Position direction);
bool addQueenCaptureMovesIfEmpty(Move *intermediateMoves, Position capturedPiecePosition, Position direction);
bool addNextQueenCaptureMoveIfPossible(Move *intermediateMoves, Position position);


#endif //CHECKERS_QUEEN_CAPTURE_H
