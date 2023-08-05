//
// Created by Jj on 08/07/2023.
//


#include "types.h"
#include "moves/captures/queenCapture.h"
#include "moves/moveUtil.h"
#include "globals.h"
#include "moves/captures/captureUtil.h"
#include "moves/captures/capture.h"


bool generateQueenCaptureMovesFrom(Position position) {
    Move *move = getStartingMove(position);
    bool noCapturePossible = tryAllDirectionsForQueenCapture(move, position);
    return !noCapturePossible;
}

bool addQueenCaptureMoves(Move *intermediateMoves, Position position, Position direction) {
    changePosition(&position, direction.row, direction.col);

    while (isOnBoard(position)) {
//        TODO: move initMove one level deeper
        initMoveIfNull(&intermediateMoves);
        if (isCaptureForbidden(position, intermediateMoves->captureCollection)) {
            return false;
        }
        if (isOpponentPiece(board[position.row][position.col])) {
            return addQueenCaptureMovesIfEmpty(intermediateMoves, position, direction);
        }
        changePosition(&position, direction.row, direction.col);
    }
    return false;
}

bool addQueenCaptureMovesIfEmpty(Move *intermediateMoves, Position capturedPiecePosition, Position direction) {
    Position to = {capturedPiecePosition.row + direction.row, capturedPiecePosition.col + direction.col};
    bool anyCapturePossible = false;

    while (isOnBoard(to) && isEmpty(board, to)) {
        anyCapturePossible = true;

        Move *moveCopy = copyMove(*intermediateMoves);
        addIntermediateMove(moveCopy, to, capturedPiecePosition);
        addNextQueenCaptureMoveIfPossible(moveCopy, to);
        changePosition(&to, direction.row, direction.col);
    }
    return anyCapturePossible;
}

bool addNextQueenCaptureMoveIfPossible(Move *intermediateMoves, Position position) {
    return addNextCaptureMoveIfPossible(intermediateMoves, position, QUEEN);
}

bool tryAllDirectionsForQueenCapture(Move *move, Position position) {
    return tryAllDirectionsForCapture(move, position, QUEEN);
}
