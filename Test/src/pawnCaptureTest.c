//
// Created by Jj on 16/07/2023.
//
#include "../Unity/src/unity.h"
#include "../include/pawnCaptureTest.h"
#include "boardSetup.h"

#include "gameEngine/playerMove.h"
#include "globals.h"


const char *pawn2CaptureMovesWIth2CapturesEachTestBoard = "../../Test/testAssets/pawn2CaptureMovesWIth2CapturesEachTestBoard.txt";
const char *twoPawns4CaptureMovesWIth2CapturesEachTestBoard = "../../Test/testAssets/2pawns4CaptureMovesWIth2CapturesEachTestBoard.txt";


void shouldYield2PawnCaptureMovesWith2CapturesEach() {
    currentPlayer = BLACK;
    read_board(board, pawn2CaptureMovesWIth2CapturesEachTestBoard);

    initPlayerMoves();
    generatePlayerMoves();

//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMovesSize);
//
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[0].toArray[0].row);
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[0].toArray[0].col);
//
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[0].toArray[1].row);
//    TEST_ASSERT_EQUAL_INT(4, playerMoves.pawnCaptureMoves[0].toArray[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[0].col);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[0].col);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[0].row);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[1].col);
}

void shouldYield4PawnCaptureMovesWith2CapturesEach() {
    currentPlayer = BLACK;
    read_board(board, twoPawns4CaptureMovesWIth2CapturesEachTestBoard);

    initPlayerMoves();
    generatePlayerMoves();

//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pawnCaptureMovesSize);
//
//    //first pawn
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[0].toArray[0].row);
//    TEST_ASSERT_EQUAL_INT(2, playerMoves.pawnCaptureMoves[0].toArray[0].col);
//
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[0].toArray[1].row);
//    TEST_ASSERT_EQUAL_INT(6, playerMoves.pawnCaptureMoves[0].toArray[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[0].col);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[0].captures[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[0].col);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[0].row);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(5, playerMoves.pawnCaptureMoves[0].captureCollections[1].captures[1].col);
//
////    second pawn
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[1].toArray[0].row);
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[1].toArray[0].col);
//
//    TEST_ASSERT_EQUAL_INT(0, playerMoves.pawnCaptureMoves[1].toArray[1].row);
//    TEST_ASSERT_EQUAL_INT(4, playerMoves.pawnCaptureMoves[1].toArray[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[1].captureCollections[0].captures[0].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[1].captureCollections[0].captures[0].col);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[1].captureCollections[0].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[1].captureCollections[0].captures[1].col);
//
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[1].captureCollections[1].captures[0].col);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[1].captureCollections[1].captures[0].row);
//
//    TEST_ASSERT_EQUAL_INT(1, playerMoves.pawnCaptureMoves[1].captureCollections[1].captures[1].row);
//    TEST_ASSERT_EQUAL_INT(3, playerMoves.pawnCaptureMoves[1].captureCollections[1].captures[1].col);
}