//
// Created by Jj on 23/07/2023.
//

#include "ui/display/UIConstants.h"
#include "types.h"
#include "ui/events/eventHandlerUtil.h"


bool isInsideBoard(int x, int y) {
    return x >= LEFT_PANEL_WIDTH && x < BOARD_SIZE * SQUARE_SIZE + LEFT_PANEL_WIDTH && y >= TOP_PANEL_HEIGHT && y < BOARD_SIZE * SQUARE_SIZE + TOP_PANEL_HEIGHT;
}

Position translateToBoardPosition(int x, int y) {
    return (Position) {BOARD_SIZE - 1 - (y - TOP_PANEL_HEIGHT) / SQUARE_SIZE, (x - LEFT_PANEL_WIDTH) / SQUARE_SIZE };
}