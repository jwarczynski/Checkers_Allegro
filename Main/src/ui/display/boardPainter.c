//
// Created by Jj on 23/07/2023.
//

#include "ui/display/boardPainter.h"

#include "allegro5/allegro_primitives.h"

#include "ui/uiState.h"
#include "types.h"
#include "ui/display/UIConstants.h"


extern Piece board[8][8];
extern UI ui;

void drawInterface() {
    al_set_target_bitmap(al_get_backbuffer(ui.display));
    al_clear_to_color(BACKGROUND_COLOR);

    drawBoard();
    drawMenu();

    al_flip_display();
}

void drawBoard() {
    al_set_target_bitmap(al_get_backbuffer(ui.display));

    drawSquares();
    drawPieces();
    drawCoordinates();
    drawBorder();

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
        return WHITE_SQUARE_COLOR;
    }
    return BLACK_SQUARE_COLOR;
}

void drawSquare(int row, int column, ALLEGRO_COLOR color) {
    float x1 = (float) column * SQUARE_SIZE + LEFT_PANEL_WIDTH;
    float y1 = (float) row * SQUARE_SIZE + TOP_PANEL_HEIGHT;
    float x2 = (float) (column + 1) * SQUARE_SIZE + LEFT_PANEL_WIDTH;
    float y2 = (float) (row + 1) * SQUARE_SIZE + TOP_PANEL_HEIGHT;
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
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
    drawPawn(row, col, WHITE_PAWN_COLOR);
}

void drawBlackPawn(int row, int col) {
    drawPawn(row, col, BLACK_PAWN_COLOR);
}

void drawWhiteQueen(int row, int col) {
    drawQueen(row, col, WHITE_PAWN_COLOR, WHITE_QUEEN_COLOR);
}
void drawBlackQueen(int row, int col) {
    drawQueen(row, col, BLACK_PAWN_COLOR, BLACK_QUEEN_COLOR);
}

void drawPawn(int row, int col, ALLEGRO_COLOR color) {
    drawPawnCircle(row, col, color);
}

void drawQueen(int row, int col, ALLEGRO_COLOR pawnColor, ALLEGRO_COLOR queenColor) {
    drawQueenCircle(row, col, queenColor);
    drawPawnCircle(row, col, pawnColor);
}

void drawPawnCircle(int row, int col, ALLEGRO_COLOR color) {
    drawFilledCircle(row, col, (float)SQUARE_SIZE / 2 - 15, color);
}

void drawQueenCircle(int row, int col, ALLEGRO_COLOR color) {
    drawFilledCircle(row, col, (float)SQUARE_SIZE / 2 - 11, color);
}

void drawFilledCircle(int row, int col, float radius, ALLEGRO_COLOR color) {
    changeToDisplayCoordinates(&row, &col);

    float center_x = (float)(col) * SQUARE_SIZE + LEFT_PANEL_WIDTH + (float)SQUARE_SIZE / 2;
    float center_y = (float)row * SQUARE_SIZE + TOP_PANEL_HEIGHT + (float)SQUARE_SIZE / 2;

    al_draw_filled_circle(center_x, center_y, radius, color);
}

void drawCoordinates() {
    drawHorizontalCoordinates();
    drawVerticalCoordinates();
}

void drawHorizontalCoordinates() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        drawHorizontalCoordinate(i);
    }
}

void drawHorizontalCoordinate(int row) {
    char coordinate = (char) ('A' + row);
    float x = (float) row * SQUARE_SIZE + LEFT_PANEL_WIDTH + (float)SQUARE_SIZE / 2;
    float y = SQUARE_SIZE * BOARD_SIZE + TOP_PANEL_HEIGHT + (float)BOTTOM_PANEL_HEIGHT / 2;

    drawCenteredText(&coordinate, ui.coordinateFont, x, y);
}

void drawVerticalCoordinates() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        drawVerticalCoordinate(i);
    }
}

void drawVerticalCoordinate(int col) {
    char coordinate = (char) ('1' + BOARD_SIZE - 1 - col);
    float x = (float)LEFT_PANEL_WIDTH / 2;
    float y = (float) col * SQUARE_SIZE + TOP_PANEL_HEIGHT + (float)SQUARE_SIZE / 2;

    drawCenteredText(&coordinate, ui.coordinateFont, x, y);
}

void drawCenteredText(const char *text, ALLEGRO_FONT *font, float x, float y) {
    int fontHeight = al_get_font_line_height(font);
    y = y - (float)fontHeight / 2;

    al_draw_text(font, COORDINATE_FONT_COLOR, x, y, ALLEGRO_ALIGN_CENTER, text);
}

void drawBorder() {
    float left = LEFT_PANEL_WIDTH - 1; // Offset to adjust for the border thickness
    float top = TOP_PANEL_HEIGHT - 1; // Offset to adjust for the border thickness
    float right = left + BOARD_SIZE * SQUARE_SIZE + 1; // Add 1 to include the rightmost edge
    float bottom = top + BOARD_SIZE * SQUARE_SIZE + 1; // Add 1 to include the bottom edge

    al_draw_rectangle(left, top, right, bottom, BOARD_BORDER_COLOR, 2);
}

void drawMenu() {
    drawSaveGameButton();
    drawLoadGameButton();
    drawNewGameButton();
    drawUndoButton();
}

void drawSaveGameButton() {
    float y = TOP_PANEL_HEIGHT + SQUARE_SIZE * 2;
    drawMenuButton(y, "Save");
}

void drawLoadGameButton() {
    float y = TOP_PANEL_HEIGHT + SQUARE_SIZE * 3;
    drawMenuButton(y, "Load");
}

void drawNewGameButton() {
    float y = TOP_PANEL_HEIGHT + SQUARE_SIZE * 4;
    drawMenuButton(y, "New");
}

void drawUndoButton() {
    float y = TOP_PANEL_HEIGHT + SQUARE_SIZE * 5;
    drawMenuButton(y, "Undo");
}

void drawMenuButton(float y, char *text) {
    float x1 = LEFT_PANEL_WIDTH + BOARD_SIZE * SQUARE_SIZE + SQUARE_SIZE ;
    float y1 = y;

    drawButton(x1, y1, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, text, ui.menuFont);
}

void drawButton(float x, float y, float width, float height, const char *text, ALLEGRO_FONT *font) {
    al_draw_filled_rectangle(x, y, x + width, y + height, BUTTON_COLOR);
    al_draw_rectangle(x, y, x + width, y + height, BUTTON_BORDER_COLOR, 2);

    drawCenteredText(text, font, x + MENU_BUTTON_WIDTH / 2, y + MENU_BUTTON_HEIGHT / 2);
}

void changeToDisplayCoordinates(int *row, int *col) {
    *row = BOARD_SIZE - *row - 1;
}