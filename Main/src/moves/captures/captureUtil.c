//
// Created by Jj on 10/07/2023.
//

#include <stdbool.h>
#include <malloc.h>
#include "moves/captures/captureUtil.h"
#include "types.h"
#include "moves/moveUtil.h"

#define MAX_QUEEN_CAPTURE_MOVES 20

extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

bool isAlreadyCaptured(CaptureCollection previousCaptures, Position position) {
    for (int i = 0; i < previousCaptures.captureSize; ++i) {
        if (previousCaptures.captures[i].row == position.row && previousCaptures.captures[i].col == position.col) {
            return true;
        }
    }
    return false;
}

void initCaptureIfNull(CaptureCollection **captures, PieceType pieceType) {
    if (*captures == NULL) {
        *captures = (CaptureCollection*)malloc(sizeof(CaptureCollection));
        (*captures)->captureSize = 0;
        (*captures)->captureAllocatedSize = 0;
        (*captures)->captures = NULL;
    }

    if ((*captures)->captures == NULL) {
        (*captures)->captures = (Position*)malloc(sizeof(Position) * MAX_QUEEN_CAPTURE_MOVES);
        (*captures)->captureAllocatedSize = MAX_QUEEN_CAPTURE_MOVES;
        (*captures)->captureSize = 0;
    }
}

void addCaptureToCaptureArray(CaptureCollection *captures, Position capturedPiecePosition) {
    captures->captures[captures->captureSize++] = capturedPiecePosition;
}

bool isCaptureForbidden(Position position, CaptureCollection captureCollection) {
    return isOutOfBounds(position) || isCurrentPlayerPiece(board[position.row][position.col]) ||
           isAlreadyCaptured(captureCollection, position);
}
