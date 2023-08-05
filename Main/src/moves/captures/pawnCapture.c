//
// Created by Jj on 15/07/2023.
//

#include <stdbool.h>
#include <malloc.h>
#include "moves/captures/pawnCapture.h"
#include "moves/captures/capture.h"
#include "moves/moveUtil.h"
#include "moves/captures/captureUtil.h"


extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


bool generatePawnCaptureMovesFrom(Position position) {
    Move *move = getStartingMove(position);
    bool noCapturesPossible = tryAllDirectionsForPawnCapture(move, position);

    return !noCapturesPossible;
}

bool tryAllDirectionsForPawnCapture(Move *intermediateMoves, Position position) {
    return tryAllDirectionsForCapture(intermediateMoves, position, PAWN);
}

bool addPawnCaptureMoves(Move *intermediateMoves, Position position, Position direction) {
    changePosition(&position, direction.row, direction.col);

    if (isOnBoard(position)) {
        initMoveIfNull(&intermediateMoves);
        if (isCaptureForbidden(position, intermediateMoves->captureCollection)) {
            return false;
        }
        if (isOpponentPiece(board[position.row][position.col])) {
            return addPawnCaptureMovesIfEmpty(intermediateMoves, position, direction);
        }
    }
    return false;
}

bool addPawnCaptureMovesIfEmpty(Move *intermediateMoves, Position capturedPiecePosition, Position direction) {
    Position to = {capturedPiecePosition.row + direction.row, capturedPiecePosition.col + direction.col};

    if (isOnBoard(to) && isEmpty(board, to)) {
        initCaptureIfNull(&intermediateMoves->captureCollection, PAWN);
        Move *moveCopy = copyMove(*intermediateMoves);
        addIntermediateMove(moveCopy, to, capturedPiecePosition);
        return addNextPawnCaptureMoveIfPossible(moveCopy, to);
    }
    return false;
}

bool addNextPawnCaptureMoveIfPossible(Move *intermediateMoves, Position position) {
    return addNextCaptureMoveIfPossible(intermediateMoves, position, PAWN);
}
