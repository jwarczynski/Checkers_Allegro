//
// Created by Jj on 14/07/2023.
//

#include "../Unity/src/unity.h"
#include "boardSetup.h"
#include "gameEngine/playerMove.h"
#include "globals.h"
#include "../include/testUtil.h"

const char *queenSingleCaptureMultipleCaptureMovesTestBoardPath = "../../Test/testAssets/queenSingleCaptureMultipleCaptureMovesTestBoard.txt";
const char *testBoardPath = "../../Test/testAssets/queen2CaptureMovesWIth2CapturesEachTestBoard.txt";



void shouldYield2QueenCaptureMovesWith2CapturesEach() {
    currentPlayer = BLACK;

    board[3][7] = BLACK_QUEEN;
    board[2][6] = WHITE_PAWN;
    board[4][2] = WHITE_QUEEN;

    generateMoves();

    TEST_ASSERT_EQUAL_INT(2, playerMoveCollection.size);
}

void shouldYield3QueenCaptureMovesWith1Capture() {
    currentPlayer = BLACK;
    read_board(board, queenSingleCaptureMultipleCaptureMovesTestBoardPath);

    initPlayerMoves();
    generatePlayerMoves();

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMovesSize);
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves->captureCollections[0].size);
//
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.queenCaptureMoves[0].toArray[0].row);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.queenCaptureMoves[0].toArray[0].col);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].toArray[1].row);
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].toArray[1].col);
//
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].toArray[2].row);
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].toArray[2].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[0].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[0].captures[0].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[1].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[1].captures[0].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[2].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captureCollections[2].captures[0].col);
}

void shouldYield5QueenCaptureMovesWith1CaptureEach() {
    currentPlayer = WHITE;
    setALlBoardToEmpty();
    board[7][6] = WHITE_QUEEN;
    board[6][5] = BLACK_PAWN;
    initPlayerMoves();
    generatePlayerMoves();

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].captureCollections[2].size);

}