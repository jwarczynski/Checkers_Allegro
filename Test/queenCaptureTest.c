//
// Created by Jj on 14/07/2023.
//

#include "Unity/src/unity.h"
#include "boardSetup.h"
#include "gameEngine/playerMove.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

const char *queenSingleCaptureMultipleCaptureMovesTestBoardPath = "../../Test/testAssets/queenSingleCaptureMultipleCaptureMovesTestBoard.txt";
const char *testBoardPath = "../../Test/testAssets/queen2CaptureMovesWIth2CapturesEachTestBoard.txt";



void shouldYield2QueenCaptureMovesWith2CapturesEach() {
    currentPlayer = BLACK;
    read_board(board, testBoardPath);

    initPlayerMoves();
    generatePlayerMoves();

    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMovesSize);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].to[0].row);
    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].to[0].col);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].to[1].row);
    TEST_ASSERT_EQUAL_INT(4, playerMoves.queenCaptureMoves[0].to[1].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[0].captures[0].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[0].captures[0].col);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].captured[0].captures[1].row);
    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].captured[0].captures[1].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[1].captures[0].col);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[1].captures[0].row);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].captured[1].captures[1].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[1].captures[1].col);
}

void shouldYield3QueenCaptureMovesWith1Capture() {
    currentPlayer = BLACK;
    read_board(board, queenSingleCaptureMultipleCaptureMovesTestBoardPath);

    initPlayerMoves();
    generatePlayerMoves();

    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMovesSize);

    TEST_ASSERT_EQUAL_INT(2, playerMoves.queenCaptureMoves[0].to[0].row);
    TEST_ASSERT_EQUAL_INT(2, playerMoves.queenCaptureMoves[0].to[0].col);

    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].to[1].row);
    TEST_ASSERT_EQUAL_INT(1, playerMoves.queenCaptureMoves[0].to[1].col);

    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].to[2].row);
    TEST_ASSERT_EQUAL_INT(0, playerMoves.queenCaptureMoves[0].to[2].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[0].captures[0].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[0].captures[0].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[1].captures[0].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[1].captures[0].col);

    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[2].captures[0].row);
    TEST_ASSERT_EQUAL_INT(3, playerMoves.queenCaptureMoves[0].captured[2].captures[0].col);
}
