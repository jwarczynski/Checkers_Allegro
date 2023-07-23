//
// Created by Jj on 23/07/2023.
//

#include "ui/boardPainter.h"

#include <allegro5/allegro_primitives.h>

#include "../../include/ui/uiState.h"
#include "types.h"
#include "ui/UIConstants.h"


extern Piece board[8][8];
extern UI ui;


void drawBoard() {
    al_set_target_bitmap(al_get_backbuffer(ui.display));
    al_clear_to_color(al_map_rgb(255, 255, 255));
    drawSquares();
    drawPieces();
    al_flip_display();
}

void drawSquares() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        drawRow(i);
    }
}

void drawRow(int row) {
    for (int col = 0; col < BOARD_SIZE; col++) {
        drawSquare(row, col, getColor(row, col));
    }
}

ALLEGRO_COLOR getColor(int row, int col) {
    if ((row + col) % 2 == 0) {
        return COLOR_WHITE;
    }
    return COLOR_BLACK;
}

void drawSquare(int row, int column, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle((float)(column) * SQUARE_SIZE, (float)row * SQUARE_SIZE, (float)(column + 1) * SQUARE_SIZE,
                             (float)(row + 1) * SQUARE_SIZE, color);
}

void drawPieces() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            drawPiece(row, col);
        }
    }
}

void drawPiece(int row, int col) {
    switch (board[row][col]) {
        case WHITE_PAWN:
            drawWhitePawn(row, col); break;
        case BLACK_PAWN:
            drawBlackPawn(row, col); break;
        case WHITE_QUEEN:
            drawWhiteQueen(row, col); break;
        case BLACK_QUEEN:
            drawBlackQueen(row, col); break;
        default:
            break;
    }
}

void drawWhitePawn(int row, int col) {
    drawPawn(row, col, al_map_rgb(255, 255, 255));
}

void drawBlackPawn(int row, int col) {
    drawPawn(row, col, al_map_rgb(0, 0, 0));
}

void drawWhiteQueen(int row, int col) {
    drawQueen(row, col, al_map_rgb(178, 123, 211));
}
void drawBlackQueen(int row, int col) {
    drawQueen(row, col, al_map_rgb(0, 0, 0));
}

void drawPawn(int row, int col, ALLEGRO_COLOR color) {
    drawPawnCircle(row, col, color);
}

void drawQueen(int row, int col, ALLEGRO_COLOR color) {
    drawQueenCircle(row, col, color);
    drawPawnCircle(row, col, color);
}

void drawPawnCircle(int row, int col, ALLEGRO_COLOR color) {
    drawFilledCircle(row, col, (float)SQUARE_SIZE / 2 - 15, color);
}

void drawQueenCircle(int row, int col, ALLEGRO_COLOR color) {
    drawFilledCircle(row, col, (float)SQUARE_SIZE / 2 - 5, color);
}

void drawFilledCircle(int row, int col, float radius, ALLEGRO_COLOR color) {
    changeToDisplayCoordinates(&row, &col);

    float center_x = (float)(col) * SQUARE_SIZE + (float)SQUARE_SIZE / 2;
    float center_y = (float)row * SQUARE_SIZE + (float)SQUARE_SIZE / 2;

    al_draw_filled_circle(center_x, center_y, radius, color);
}

void changeToDisplayCoordinates(int *row, int *col) {
    *row = BOARD_SIZE - *row - 1;
}
