//
// Created by Jj on 22/07/2023.
//

#include "../include/gameEngineTest.h"
#include "gameEngine/gameEngine.h"
#include "../Unity/src/unity.h"
#include "gameEngine/playerMove.h"
#include "input/consoleInputParser.h"
#include "globals.h"
#include "boardSetup.h"


void shouldReturn2Positions() {
    initPlayerMoves();
    int count;
    Position *path = parseUserInput("A1 B2 #", &count);

    TEST_ASSERT_EQUAL_INT(2, count);

    TEST_ASSERT_EQUAL_INT(0, path[0].row);
    TEST_ASSERT_EQUAL_INT(0, path[0].col);

    TEST_ASSERT_EQUAL_INT(1, path[1].row);
    TEST_ASSERT_EQUAL_INT(1, path[1].col);
}

void shouldGenerate7MovesForWhiteInFirstTurn() {
    setupBoard(board);
    currentPlayer = WHITE;
    generateMoves();

    TEST_ASSERT_EQUAL_INT(7, playerMoveCollection.size);
}

void shouldGenerate7MovesForBlackInFirstTurn() {
    setupBoard(board);
    currentPlayer = BLACK;
    generateMoves();

    TEST_ASSERT_EQUAL_INT(7, playerMoveCollection.size);
}

void shouldGenerate2QueenCaptureMoves() {
    currentPlayer = WHITE;
    board[4][2] = WHITE_QUEEN;
    board[5][3] = BLACK_PAWN;

    generateMoves();

    TEST_ASSERT_EQUAL_INT(2, playerMoveCollection.size);
}

void shouldGenerate1QueenCaptureMoveWith2Captures() {
    currentPlayer = WHITE;
    board[2][0] = WHITE_QUEEN;
    board[4][2] = BLACK_PAWN;
    board[6][4] = BLACK_PAWN;

    generateMoves();

    TEST_ASSERT_EQUAL_INT(1, playerMoveCollection.size);
    TEST_ASSERT_EQUAL_INT(2, playerMoveCollection.moves[0].captureCollection.size);

    TEST_ASSERT_EQUAL_INT(4, playerMoveCollection.moves[0].captureCollection.captures[0].row);
    TEST_ASSERT_EQUAL_INT(2, playerMoveCollection.moves[0].captureCollection.captures[0].col);

    TEST_ASSERT_EQUAL_INT(6, playerMoveCollection.moves[0].captureCollection.captures[1].row);
    TEST_ASSERT_EQUAL_INT(4, playerMoveCollection.moves[0].captureCollection.captures[1].col);

    TEST_ASSERT_EQUAL_INT(2, playerMoveCollection.moves[0].positionPath.path[0].row);
    TEST_ASSERT_EQUAL_INT(0, playerMoveCollection.moves[0].positionPath.path[0].col);

    TEST_ASSERT_EQUAL_INT(5, playerMoveCollection.moves[0].positionPath.path[1].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoveCollection.moves[0].positionPath.path[1].col);

    TEST_ASSERT_EQUAL_INT(7, playerMoveCollection.moves[0].positionPath.path[2].row);
    TEST_ASSERT_EQUAL_INT(5, playerMoveCollection.moves[0].positionPath.path[2].col);
}