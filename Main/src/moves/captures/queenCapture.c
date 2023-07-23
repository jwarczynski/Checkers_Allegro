//
// Created by Jj on 08/07/2023.
//

#include <malloc.h>

#include "types.h"
#include "moves/captures/queenCapture.h"
#include "moves/moveUtil.h"
#include "moves/captures/captureUtil.h"
#include "moves/captures/capture.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


void generateQueenCaptureMovesFrom(Position position) {
    initQueenCaptureMovesFrom(position);
    tryAllDirectionsForQueenCapture(NULL, position);

    if (playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].size != 0) {
        playerMoves.queenCaptureMovesSize ++;
    }
}

void initQueenCaptureMovesFrom(Position position) {
    playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].size = 0;
    playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].from = position;
    playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].toArray = (Position*) malloc(sizeof(Position) * MAX_QUEEN_CAPTURE_MOVES);
    playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].captureCollections = (CaptureCollection *) malloc(sizeof(CaptureCollection) * MAX_QUEEN_CAPTURE_MOVES);
    playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].allocatedSize = MAX_QUEEN_CAPTURE_MOVES;

    markAllCaptureCollectionsAsNotInitialized(playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize].captureCollections, 0 , MAX_QUEEN_CAPTURE_MOVES);
}

bool addQueenCaptureMoves(CaptureCollection *previousCaptures, Position position, Position direction) {
    PieceCaptureMoves *queenCaptureMoves = playerMoves.queenCaptureMoves;
    changePosition(&position, direction.row, direction.col);

    while (isOnBoard(position)) {
        initCaptureIfNull(&previousCaptures, QUEEN);
        if (isCaptureForbidden(position, *previousCaptures)) {
            return false;
        }
        if (isOpponentPiece(board[position.row][position.col])) {
            return addQueenCaptureMovesIfEmpty(previousCaptures, position, direction);
        }
        changePosition(&position, direction.row, direction.col);
    }
    return false;
}

bool addQueenCaptureMovesIfEmpty(CaptureCollection *previousCaptures, Position capturedPiecePosition, Position direction) {
    Position to = {capturedPiecePosition.row + direction.row, capturedPiecePosition.col + direction.col};
    bool anyCapturePossible = false;

    while (isOnBoard(to) && isEmpty(board, to)) {
        anyCapturePossible = true;
        initCaptureIfNull(&previousCaptures, QUEEN);
        CaptureCollection *previousCapturesCopy = copyCapture(*previousCaptures);
        addCaptureToCaptureArray(previousCapturesCopy, capturedPiecePosition);
        addNextQueenCaptureMoveIfPossible(previousCapturesCopy, to);
        changePosition(&to, direction.row, direction.col);
    }
    return anyCapturePossible;
}

bool addNextQueenCaptureMoveIfPossible(CaptureCollection *previousCaptures, Position position) {
    return addNextCaptureMoveIfPossible(previousCaptures, position, QUEEN);
}

bool tryAllDirectionsForQueenCapture(CaptureCollection *previousCaptures, Position position) {
    return tryAllDirectionsForCapture(previousCaptures, position, QUEEN);
}

void saveQueenPositionAndCaptures(CaptureCollection *captureCollection, Position position) {
    PieceCaptureMoves *queenCaptureMoves = &(playerMoves.queenCaptureMoves[playerMoves.queenCaptureMovesSize]);
    queenCaptureMoves->toArray[queenCaptureMoves->size] = position;
    queenCaptureMoves->captureCollections[queenCaptureMoves->size] = *captureCollection;
    queenCaptureMoves->size++;
}

void deallocateCaptureMoves(PieceCaptureMoves *pieceCaptureMoves) {
    free(pieceCaptureMoves->captureCollections);
    free(pieceCaptureMoves->toArray);
    free(pieceCaptureMoves);
}

void reallocateQueenCaptureMoves(PieceCaptureMoves *queenCaptureMoves) {
    queenCaptureMoves->captureCollections = realloc(queenCaptureMoves->captureCollections, sizeof(CaptureCollection) * queenCaptureMoves->size);
    queenCaptureMoves->toArray = realloc(queenCaptureMoves->toArray, sizeof(Position) * queenCaptureMoves->size);
    queenCaptureMoves->allocatedSize = queenCaptureMoves->size;
}
