//
// Created by Jj on 23/07/2023.
//

#include "ui/UIConstants.h"
#include "types.h"
#include "ui/eventHandlerUtil.h"


bool isInsideBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE * SQUARE_SIZE && y >= 0 && y < BOARD_SIZE * SQUARE_SIZE;
}

Position translateToBoardPosition(int x, int y) {
    return (Position) {BOARD_SIZE - 1 - y / SQUARE_SIZE, x / SQUARE_SIZE};
}