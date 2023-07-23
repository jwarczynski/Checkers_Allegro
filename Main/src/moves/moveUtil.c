//
// Created by Jj on 08/07/2023.
//

#include <malloc.h>
#include <string.h>
#include "moves/moveUtil.h"


extern Player currentPlayer;
extern PlayerMoves playerMoves;


bool isWhitePiece(Piece piece) {
    return piece == WHITE_PAWN || piece == WHITE_QUEEN;
}

bool isBlackPiece(Piece piece) {
    return piece == BLACK_PAWN || piece == BLACK_QUEEN;
}

bool isOnBoard(Position position) {
    return position.row >= 0 && position.row < BOARD_SIZE && position.col >= 0 && position.col < BOARD_SIZE;
}

bool isQueen(Piece piece) {
    return piece == WHITE_QUEEN || piece == BLACK_QUEEN;
}

bool isPawn(Piece piece) {
    return piece == WHITE_PAWN || piece == BLACK_PAWN;
}

bool isCurrentPlayerPiece(Piece piece) {
    return (currentPlayer == WHITE && isWhitePiece(piece)) || (currentPlayer == BLACK && isBlackPiece(piece));
}

bool isOpponentPiece(Piece piece) {
    return (currentPlayer == WHITE && isBlackPiece(piece)) || (currentPlayer == BLACK && isWhitePiece(piece));
}

bool isOutOfBounds(Position position) {
    return !isOnBoard(position);
}

bool isEmpty(Piece board[8][8], Position position) {
    return board[position.row][position.col] == EMPTY;
}

void changePosition(Position *position, int row, int col) {
    position->row += row;
    position->col += col;
}

CaptureCollection *copyCapture(CaptureCollection capture) {
    CaptureCollection *copy = malloc(sizeof(CaptureCollection));
    copy->captures = malloc(sizeof(Position) * capture.captureAllocatedSize);
    memcpy(copy->captures, capture.captures, sizeof(Position) * capture.captureAllocatedSize);
    copy->captureSize = capture.captureSize;
    copy->captureAllocatedSize = capture.captureAllocatedSize;
    return copy;
}

void initPlayerMoves() {
    if (playerMoves.queenCaptureMovesAllocatedSize == 0 || playerMoves.pawnCaptureMovesAllocatedSize == 0 ||
        playerMoves.pieceMovesAllocatedSize == 0) {

        playerMoves.queenCaptureMoves = malloc(sizeof(PieceCaptureMoves) * MAX_QUEEN_CAPTURE_MOVES);
        playerMoves.pawnCaptureMoves = malloc(sizeof(PieceCaptureMoves) * MAX_QUEEN_CAPTURE_MOVES);
        playerMoves.pieceMoves = malloc(sizeof(PieceMoves) * MAX_QUEEN_CAPTURE_MOVES);

        playerMoves.queenCaptureMovesSize = 0;
        playerMoves.pawnCaptureMovesSize = 0;
        playerMoves.pieceMovesSize = 0;

        playerMoves.queenCaptureMovesAllocatedSize = MAX_QUEEN_CAPTURE_MOVES;
        playerMoves.pawnCaptureMovesAllocatedSize = MAX_QUEEN_CAPTURE_MOVES;
        playerMoves.pieceMovesAllocatedSize = MAX_QUEEN_CAPTURE_MOVES;

        markAllMovesAsNotInitialized();
    }
}

void markAllMovesAsNotInitialized() {
   markMovesAsNotInitialized(0, MAX_QUEEN_CAPTURE_MOVES);
}

void markMovesAsNotInitialized(int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; ++i) {
        playerMoves.queenCaptureMoves[i].toArray = NULL;
        playerMoves.queenCaptureMoves[i].captureCollections = NULL;
        playerMoves.queenCaptureMoves[i].allocatedSize = 0;

        playerMoves.pawnCaptureMoves[i].toArray = NULL;
        playerMoves.pawnCaptureMoves[i].captureCollections = NULL;
        playerMoves.pawnCaptureMoves[i].allocatedSize = 0;

        playerMoves.pieceMoves[i].to = NULL;
        playerMoves.pieceMoves[i].allocatedSize = 0;
    }
}