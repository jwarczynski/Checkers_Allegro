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


void generatePawnCaptureMovesFrom(Position position) {
    initPawnCaptureMovesFrom(position);
    tryAllDirectionsForPawnCapture(NULL, position);

    if (playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].size != 0) {
        playerMoves.pawnCaptureMovesSize ++;
    }
}

void initPawnCaptureMovesFrom(Position position) {
    playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].size = 0;
    playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].from = position;
    playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].toArray = (Position*) malloc(sizeof(Position) * MAX_QUEEN_CAPTURE_MOVES);
    playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].captureCollections = (CaptureCollection *) malloc(sizeof(CaptureCollection) * MAX_QUEEN_CAPTURE_MOVES);
    playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].allocatedSize = MAX_QUEEN_CAPTURE_MOVES;

    markAllCaptureCollectionsAsNotInitialized(playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize].captureCollections, 0 , MAX_QUEEN_CAPTURE_MOVES);
}

bool tryAllDirectionsForPawnCapture(CaptureCollection *previousCaptures, Position position) {
    return tryAllDirectionsForCapture(previousCaptures, position, PAWN);
}

bool addPawnCaptureMoves(CaptureCollection *previousCaptures, Position position, Position direction) {
    PieceCaptureMoves *pawnCaptureMoves = playerMoves.pawnCaptureMoves;
    changePosition(&position, direction.row, direction.col);

    if (isOnBoard(position)) {
        initCaptureIfNull(&previousCaptures, PAWN);
        if (isCaptureForbidden(position, *previousCaptures)) {
            return false;
        }
        if (isOpponentPiece(board[position.row][position.col])) {
            return addPawnCaptureMovesIfEmpty(previousCaptures, position, direction);
        }
    }
    return false;
}

bool addPawnCaptureMovesIfEmpty(CaptureCollection *previousCaptures, Position capturedPiecePosition, Position direction) {
    Position to = {capturedPiecePosition.row + direction.row, capturedPiecePosition.col + direction.col};

    if (isOnBoard(to) && isEmpty(board, to)) {
        initCaptureIfNull(&previousCaptures, PAWN);
        CaptureCollection *previousCapturesCopy = copyCapture(*previousCaptures);
        addCaptureToCaptureArray(previousCapturesCopy, capturedPiecePosition);
        return addNextPawnCaptureMoveIfPossible(previousCapturesCopy, to);
    }
    return false;
}

bool addNextPawnCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position) {
    return addNextCaptureMoveIfPossible(previousCaptures, position, PAWN);
}

void savePawnPositionAndCapture(CaptureCollection *captureCollection, Position position) {
    PieceCaptureMoves *pawnCaptureMoves = &(playerMoves.pawnCaptureMoves[playerMoves.pawnCaptureMovesSize]);
    pawnCaptureMoves->toArray[pawnCaptureMoves->size] = position;
    pawnCaptureMoves->captureCollections[pawnCaptureMoves->size] = *captureCollection;
    pawnCaptureMoves->size++;
}