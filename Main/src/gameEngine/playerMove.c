//
// Created by Jj on 08/07/2023.
//

#include "gameEngine/playerMove.h"
#include "moves/moveUtil.h"
#include "moves/captures/queenCapture.h"
#include "moves/moves/queenMove.h"
#include "moves/moves/pawnMove.h"
#include "moves/captures/pawnCapture.h"

extern Player currentPlayer;
extern PlayerMoveCollection playerMoveCollection;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void generatePlayerMoves() {
    initPlayerMoves();
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            generateNoCaptureMovesByType((Position) {row, col});
        }
    }
}

void generateNoCaptureMovesByType(Position position) {
    if (isCurrentPlayerPiece(board[position.row][position.col]) && isQueen(board[position.row][position.col])) {
        generateQueenMovesFrom(position);
    } else if (isCurrentPlayerPiece(board[position.row][position.col]) && isPawn(board[position.row][position.col])) {
        generatePawnMovesFrom(position);
    }
}

PlayerMoves getEmptyPlayerMoves() {
    PlayerMoves emptyPLayerMoves;
    emptyPLayerMoves.pieceMovesSize = 0;
    emptyPLayerMoves.pawnCaptureMovesSize = 0;
    emptyPLayerMoves.queenCaptureMovesSize = 0;
    return emptyPLayerMoves;

}

void generateMoves() {
    generateQueenCaptureMoves();
    if (playerMoveCollection.size > 0) {
        return;
    }

    generatePawnCaptureMoves();
    if (playerMoveCollection.size > 0) {
        return;
    }

    generateNoCaptureMoves();
}

bool generateQueenCaptureMoves() {
    return performMoveOperationForEachSquare(generateQueenCapturesIfPlayerQueen);
}

bool generateQueenCapturesIfPlayerQueen(Position position) {
    if (isCurrentPlayerPiece(board[position.row][position.col]) && isQueen(board[position.row][position.col])) {
        return generateQueenCaptureMovesFrom(position);
    }
}

bool generatePawnCaptureMoves() {
    return performMoveOperationForEachSquare(generatePawnCapturesIfPlayerPawn);
}

bool generatePawnCapturesIfPlayerPawn(Position position) {
    if (isCurrentPlayerPiece(board[position.row][position.col]) && isPawn(board[position.row][position.col])) {
        return generatePawnCaptureMovesFrom(position);
    }
}

bool performMoveOperationForEachSquare(bool (*operation)(Position)) {
    bool anyMoves = false;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (operation((Position) {row, col})) {
                anyMoves = true;
            };
        }
    }
    return anyMoves;
}

void generateNoCaptureMoves() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            generateNoCaptureMovesByType((Position) {row, col});
        }
    }
}
