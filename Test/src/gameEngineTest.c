//
// Created by Jj on 22/07/2023.
//

#include "../include/gameEngineTest.h"
#include "gameEngine/gameEngine.h"
#include "../Unity/src/unity.h"
#include "gameEngine/playerMove.h"
#include "input/consoleInputParser.h"


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