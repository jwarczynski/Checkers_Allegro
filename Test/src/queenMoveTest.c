//
// Created by Jj on 21/07/2023.
//

#include "types.h"
#include "../include/testUtil.h"
#include "moves/moves/queenMove.h"
#include "../Unity/src/unity.h"
#include "globals.h"


void shouldYield2MovesOnEachDiagonalPieceStop(enum Piece piece);

void shouldYield7MovesOnOneDiagonal() {
    setALlBoardToEmpty();
    Position from = {0, 0};
    board[0][0] = WHITE_QUEEN;
    generateQueenMovesFrom(from);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize);
    TEST_ASSERT_EQUAL_INT(7, playerMoves.pieceMoves[0].size);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[0].row);
    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[0].col);

    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].to[1].row);
    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].to[1].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[2].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[2].col);

    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[3].row);
    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[3].col);

    TEST_ASSERT_EQUAL_INT(5, playerMoves.pieceMoves[0].to[4].row);
    TEST_ASSERT_EQUAL_INT(5, playerMoves.pieceMoves[0].to[4].col);

    TEST_ASSERT_EQUAL_INT(6, playerMoves.pieceMoves[0].to[5].row);
    TEST_ASSERT_EQUAL_INT(6, playerMoves.pieceMoves[0].to[5].col);

    TEST_ASSERT_EQUAL_INT(7, playerMoves.pieceMoves[0].to[6].row);
    TEST_ASSERT_EQUAL_INT(7, playerMoves.pieceMoves[0].to[6].col);
}

void shouldYieldNoMoves() {
    setALlBoardToEmpty();
    Position from = {2, 2};
    currentPlayer = WHITE;
    board[2][2] = WHITE_QUEEN;
    board[1][1] = WHITE_PAWN;
    board[3][3] = BLACK_PAWN;
    board[3][1] = BLACK_PAWN;
    board[1][3] = BLACK_PAWN;
    generateQueenMovesFrom(from);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMovesSize);
    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMoves[0].size);
}

void shouldYield2MovesOnEachDiagonalOpponentStop() {
    return shouldYield2MovesOnEachDiagonalPieceStop(BLACK_PAWN);
}

void shouldYield2MovesOnEachDiagonalOpponentQueenStop() {
    return shouldYield2MovesOnEachDiagonalPieceStop(BLACK_QUEEN);
}

void shouldYield2MovesOnEachDiagonalOwnQueenStop() {
    return shouldYield2MovesOnEachDiagonalPieceStop(WHITE_QUEEN);
}

void shouldYield2MovesOnEachDiagonalOwnPawnStop() {
    return shouldYield2MovesOnEachDiagonalPieceStop(WHITE_PAWN);
}

void shouldYield2MovesOnEachDiagonalPieceStop(Piece piece) {
    setALlBoardToEmpty();
    Position from = {2, 2};
    board[2][2] = WHITE_QUEEN;
    board[5][5] = piece;

    generateQueenMovesFrom(from);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize);
    TEST_ASSERT_EQUAL_INT(8, playerMoves.pieceMoves[0].size);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[0].row);
    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[0].col);

    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[1].row);
    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMoves[0].to[1].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[2].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[2].col);

    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[3].row);
    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[3].col);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[4].row);
    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[4].col);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMoves[0].to[5].row);
    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMoves[0].to[5].col);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].to[6].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.pieceMoves[0].to[6].col);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.pieceMoves[0].to[7].row);
    TEST_ASSERT_EQUAL_INT(4, playerMoves.pieceMoves[0].to[7].col);
}
