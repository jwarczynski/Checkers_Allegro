//
// Created by Jj on 08/07/2023.
//

#include <malloc.h>
#include "gameEngine/playerMove.h"
#include "moves/moveUtil.h"
#include "moves/captures/queenCapture.h"
#include "moves/moves/queenMove.h"
#include "moves/moves/pawnMove.h"
#include "moves/captures/pawnCapture.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void generatePlayerMoves() {
    initPlayerMoves();
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            generateMovesByType((Position) {row, col});
        }
    }
}

void generateMovesByType(Position position) {
    if (isCurrentPlayerPiece(board[position.row][position.col]) && isQueen(board[position.row][position.col])) {
        generateQueenCaptureMovesFrom(position);
        generateQueenMovesFrom(position);
    }
    if (isCurrentPlayerPiece(board[position.row][position.col]) && isPawn(board[position.row][position.col])) {
        generatePawnCaptureMovesFrom(position);
        generatePawnMovesFrom(position);
    }
}

void deallocatePlayerMovesMemory() {
    for (int i = 0; i < playerMoves.queenCaptureMovesAllocatedSize; i++) {
        for (int j = 0; j < playerMoves.queenCaptureMoves[i].allocatedSize; j++) {
            if (playerMoves.queenCaptureMoves[i].captured[j].captureAllocatedSize > 0) {
                free(playerMoves.queenCaptureMoves[i].captured[j].captures);
            }
        }
        free(playerMoves.queenCaptureMoves[i].captured);
        free(playerMoves.queenCaptureMoves[i].to);
    }

    for (int i = 0; i < playerMoves.pawnCaptureMovesAllocatedSize; i++) {
        for (int j = 0; j < playerMoves.pawnCaptureMoves[i].allocatedSize; j++) {
            if (playerMoves.pawnCaptureMoves[i].captured[j].captureAllocatedSize > 0) {
                free(playerMoves.pawnCaptureMoves[i].captured[j].captures);
            }
        }
        free(playerMoves.pawnCaptureMoves[i].captured);
        free(playerMoves.pawnCaptureMoves[i].to);
    }

    for (int i = 0; i < playerMoves.pieceMovesAllocatedSize; i++) {
        free(playerMoves.pieceMoves[i].to);
    }

    free(playerMoves.queenCaptureMoves);
    free(playerMoves.pawnCaptureMoves);
    free(playerMoves.pieceMoves);

    playerMoves.queenCaptureMoves = NULL;
    playerMoves.pawnCaptureMoves = NULL;
    playerMoves.pieceMoves = NULL;

    playerMoves.queenCaptureMovesSize = 0;
    playerMoves.pawnCaptureMovesSize = 0;
    playerMoves.pieceMovesSize = 0;

    playerMoves.queenCaptureMovesAllocatedSize = 0;
    playerMoves.pawnCaptureMovesAllocatedSize = 0;
    playerMoves.pieceMovesAllocatedSize = 0;
}

PlayerMoves getEmptyPlayerMoves() {
    PlayerMoves emptyPLayerMoves;
    emptyPLayerMoves.pieceMovesSize = 0;
    emptyPLayerMoves.pawnCaptureMovesSize = 0;
    emptyPLayerMoves.queenCaptureMovesSize = 0;
    return emptyPLayerMoves;

}
