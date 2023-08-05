//
// Created by Jj on 20/07/2023.
//

#include "../include/pawnMoveTest.h"
#include "types.h"
#include "moves/moves/pawnMove.h"
#include "../Unity/src/unity.h"
#include "gameEngine/playerMove.h"
#include "../include/testUtil.h"
#include "globals.h"



void shouldYield2WhitePawnMoves() {
    Position from = {1, 1};
    Position to1 = {2, 0};
    Position to2 = {2, 2};

    currentPlayer = WHITE;
    board[from.row][from.col] = WHITE_PAWN;
    board[to1.row][to1.col] = EMPTY;
    board[to2.row][to2.col] = EMPTY;

    initPlayerMoves();
    generatePawnMovesFrom(from);

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].size);
//
//    TEST_ASSERT_EQUAL_INT(to1.row, playerMoves.pieceMoves[0].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to1.col, playerMoves.pieceMoves[0].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to2.row, playerMoves.pieceMoves[0].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to2.col, playerMoves.pieceMoves[0].to[1].col);
}

void shouldYield1WhitePawnMove() {
    Position from = {1, 1};
    Position to = {2, 0};

    currentPlayer = WHITE;
    board[from.row][from.col] = WHITE_PAWN;
    board[to.row][to.col] = EMPTY;
    board[2][2] = BLACK_PAWN;

    initPlayerMoves();
    generatePawnMovesFrom(from);

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize);
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMoves[0].size);
//
//    TEST_ASSERT_EQUAL_INT(to.row, playerMoves.pieceMoves[0].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to.col, playerMoves.pieceMoves[0].to[0].col);

}

void shouldYield2BlackPawnMoves() {
    Position from = {6, 1};
    Position to1 = {5, 0};
    Position to2 = {5, 2};

    currentPlayer = BLACK;
    board[from.row][from.col] = BLACK_PAWN;
    board[to1.row][to1.col] = EMPTY;
    board[to2.row][to2.col] = EMPTY;

    initPlayerMoves();
    generatePawnMovesFrom(from);

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].size);
//
//    TEST_ASSERT_EQUAL_INT(to1.row, playerMoves.pieceMoves[0].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to1.col, playerMoves.pieceMoves[0].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to2.row, playerMoves.pieceMoves[0].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to2.col, playerMoves.pieceMoves[0].to[1].col);
}

void shouldYield1BlackPawnMove() {
    Position from = {6, 1};
    Position to = {5, 0};

    currentPlayer = BLACK;
    board[from.row][from.col] = BLACK_PAWN;
    board[to.row][to.col] = EMPTY;
    board[5][2] = WHITE_PAWN;

    initPlayerMoves();
    generatePawnMovesFrom(from);

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pieceMovesSize)

}

void shouldYield2WhitePawnsWith2MovesEach() {
    Position from1 = {1, 1};
    Position to11 = {2, 0};
    Position to12 = {2, 2};

    Position from2 = {6, 1};
    Position to21 = {7, 0};
    Position to22 = {7, 2};

    currentPlayer = WHITE;
    board[from1.row][from1.col] = WHITE_PAWN;
    board[from2.row][from2.col] = WHITE_PAWN;
    board[to11.row][to11.col] = EMPTY;
    board[to12.row][to12.col] = EMPTY;
    board[to21.row][to21.col] = EMPTY;
    board[to22.row][to22.col] = EMPTY;

    initPlayerMoves();
    generatePawnMovesFrom(from1);
    generatePawnMovesFrom(from2);

//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMovesSize);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].size);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[1].size);
//
//    TEST_ASSERT_EQUAL_INT(to11.row, playerMoves.pieceMoves[0].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to11.col, playerMoves.pieceMoves[0].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to12.row, playerMoves.pieceMoves[0].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to12.col, playerMoves.pieceMoves[0].to[1].col);
//
//    TEST_ASSERT_EQUAL_INT(to21.row, playerMoves.pieceMoves[1].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to21.col, playerMoves.pieceMoves[1].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to22.row, playerMoves.pieceMoves[1].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to22.col, playerMoves.pieceMoves[1].to[1].col);
}

void shouldYield2WhitePlayerPawnsWith2MovesEach() {
    Position from1 = {1, 1};
    Position to11 = {2, 0};
    Position to12 = {2, 2};

    Position from2 = {6, 1};
    Position to21 = {7, 0};
    Position to22 = {7, 2};

    currentPlayer = WHITE;
    setALlBoardToEmpty();
    board[from1.row][from1.col] = WHITE_PAWN;
    board[from2.row][from2.col] = WHITE_PAWN;
    board[to11.row][to11.col] = EMPTY;
    board[to12.row][to12.col] = EMPTY;
    board[to21.row][to21.col] = EMPTY;
    board[to22.row][to22.col] = EMPTY;

    initPlayerMoves();
    generatePlayerMoves();

//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMovesSize);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[0].size);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pieceMoves[1].size);
//
//    TEST_ASSERT_EQUAL_INT(to11.row, playerMoves.pieceMoves[0].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to11.col, playerMoves.pieceMoves[0].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to12.row, playerMoves.pieceMoves[0].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to12.col, playerMoves.pieceMoves[0].to[1].col);
//
//    TEST_ASSERT_EQUAL_INT(to21.row, playerMoves.pieceMoves[1].to[0].row);
//    TEST_ASSERT_EQUAL_INT(to21.col, playerMoves.pieceMoves[1].to[0].col);
//
//    TEST_ASSERT_EQUAL_INT(to22.row, playerMoves.pieceMoves[1].to[1].row);
//    TEST_ASSERT_EQUAL_INT(to22.col, playerMoves.pieceMoves[1].to[1].col);
}
