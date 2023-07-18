//
// Created by Jj on 15/07/2023.
//

#include "Unity/src/unity.h"
#include "boardSetup.h"
#include "gameEngine/playerMove.h"

#include "queenCaptureTest.h"
#include "pawnCaptureTest.h"

extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


void setUp() {}
void tearDown() {
    deallocatePlayerMovesMemory();
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(shouldYield2QueenCaptureMovesWith2CapturesEach);
    RUN_TEST(shouldYield3QueenCaptureMovesWith1Capture);
    RUN_TEST(shouldYield2PawnCaptureMovesWith2CapturesEach);
    RUN_TEST(shouldYield4PawnCaptureMovesWith2CapturesEach);
    UNITY_END();
}