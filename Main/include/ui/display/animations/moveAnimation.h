//
// Created by Jj on 28/07/2023.
//

#ifndef CHECKERS_MOVE_ANIMATION_H
#define CHECKERS_MOVE_ANIMATION_H

#include "types.h"

void animateMove(Move move);
void animateIntermediateMove(Position from, Position to, Position capturedPiecePosition);

float lerp(float start, float end, float t);

UISquare **translateToDisplayPositions();
void translateToDisplayPosition(UISquare *piece, int row, int col);
void defineSquareMiddle(float *x, float *y, int row, int col);

#endif //CHECKERS_MOVE_ANIMATION_H
