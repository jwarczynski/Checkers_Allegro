//
// Created by Jj on 15/07/2023.
//

#include "Unity/src/unity.h"
#include "include/testUtil.h"
#include "moves/moveUtil.h"
#include "gameEngine/playerMove.h"
#include "include/gameEngineTest.h"
#include "include/queenCaptureTest.h"



void setUp() {
    initPlayerMoves();
    setALlBoardToEmpty();
}
void tearDown() {
    destroyPlayerMoves();
}

int main() {
    UNITY_BEGIN();


    RUN_TEST(shouldGenerate7MovesForWhiteInFirstTurn);
    RUN_TEST(shouldGenerate7MovesForBlackInFirstTurn);

    RUN_TEST(shouldGenerate2QueenCaptureMoves);
    RUN_TEST(shouldGenerate1QueenCaptureMoveWith2Captures);
//
    RUN_TEST(shouldYield2QueenCaptureMovesWith2CapturesEach);


//    // QUEEN CAPTURE TESTS
//    RUN_TEST(shouldYield2QueenCaptureMovesWith2CapturesEach);
//    RUN_TEST(shouldYield3QueenCaptureMovesWith1Capture);
//    RUN_TEST(shouldYield5QueenCaptureMovesWith1CaptureEach);
//
//    // PAWN CAPTURE TESTS
//    RUN_TEST(shouldYield2PawnCaptureMovesWith2CapturesEach);
//    RUN_TEST(shouldYield4PawnCaptureMovesWith2CapturesEach);
//
//    // PAWN MOVE TESTS
//    RUN_TEST(shouldYield2WhitePawnMoves);
//    RUN_TEST(shouldYield1WhitePawnMove);
//    RUN_TEST(shouldYield2BlackPawnMoves);
//    RUN_TEST(shouldYield1BlackPawnMove);
//    RUN_TEST(shouldYield2WhitePawnsWith2MovesEach);
//
//    // QUEEN MOVE TESTS
//    RUN_TEST(shouldYield7MovesOnOneDiagonal);
//    RUN_TEST(shouldYieldNoMoves);
//    RUN_TEST(shouldYield2MovesOnEachDiagonalOpponentStop);
//    RUN_TEST(shouldYield2MovesOnEachDiagonalOwnPawnStop);
//    RUN_TEST(shouldYield2MovesOnEachDiagonalOpponentQueenStop);
//    RUN_TEST(shouldYield2MovesOnEachDiagonalOwnQueenStop);
//
//    // PLAYER MOVE TESTS
//    RUN_TEST(shouldYield2WhitePlayerPawnsWith2MovesEach);
//
//    // GAME ENGINE TESTS
//    RUN_TEST(shouldReturn2Positions);


    UNITY_END();
}