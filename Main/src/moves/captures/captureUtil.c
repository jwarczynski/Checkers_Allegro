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
    for (int i = 0; i < previousCaptures.size; ++i) {
        if (previousCaptures.captures[i].row == position.row && previousCaptures.captures[i].col == position.col) {
            return true;
        }
    }
    return false;
}

void initCaptureIfNull(CaptureCollection *captures, PieceType pieceType) {
    if ((*captures).captures == NULL) {
        (*captures).captures = (Position*)malloc(sizeof(Position) * INITIAL_CAPTURES_CAPACITY);
        (*captures).allocatedSize = INITIAL_CAPTURES_CAPACITY;
        (*captures).size = 0;
    }
}

void addIntermediateMove(Move *intermediateMoves, Position to, Position capturePosition) {
    intermediateMoves->positionPath.path[intermediateMoves->positionPath.size++] = to;
    intermediateMoves->captureCollection.captures[intermediateMoves->captureCollection.size++] = capturePosition;
}

void addCaptureToCaptureArray(CaptureCollection *captures, Position capturedPiecePosition) {
    captures->captures[captures->size++] = capturedPiecePosition;
}

bool isCaptureForbidden(Position position, CaptureCollection captureCollection) {
    return isOutOfBounds(position) || isCurrentPlayerPiece(board[position.row][position.col]) ||
           isAlreadyCaptured(captureCollection, position);
}
