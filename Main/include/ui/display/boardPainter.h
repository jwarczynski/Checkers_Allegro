//
// Created by Jj on 23/07/2023.
//

#ifndef CHECKERS_BOARD_PAINTER_H
#define CHECKERS_BOARD_PAINTER_H

#include "allegro5/color.h"
#include "allegro5/allegro_font.h"
#include "types.h"

// INTERFACE
void drawInterface();
void drawBoard();

// implementation
void drawSquares();
void drawRow(int row);
void drawSquare(int row, int column, ALLEGRO_COLOR color);

void drawCoordinates();
void drawHorizontalCoordinates();
void drawHorizontalCoordinate(int row);
void drawVerticalCoordinates();
void drawVerticalCoordinate(int col);
void drawCenteredText(const char *text, ALLEGRO_FONT *font, float x, float y);

void drawBorder();

void drawPieces();
void drawPiece(int row, int col);

ALLEGRO_COLOR getColor(int row, int col);


void drawWhitePawn(int row, int col);
void drawBlackPawn(int row, int col);
void drawWhiteQueen(int row, int col);
void drawBlackQueen(int row, int col);
void drawPawn(int row, int col, ALLEGRO_COLOR color);
void drawQueen(int row, int col, ALLEGRO_COLOR pawnColor, ALLEGRO_COLOR queenColor);

void drawPawnCircle(int row, int col, ALLEGRO_COLOR color);
void drawQueenCircle(int row, int col, ALLEGRO_COLOR color);
void drawFilledCircle(int row, int col, float radius, ALLEGRO_COLOR color);

void drawMenu();

void drawSaveGameButton();
void drawLoadGameButton();
void drawNewGameButton();
void drawUndoButton();
void drawMenuButton(float y, char *text);
void drawButton(float x, float y, float width, float height, const char *text, ALLEGRO_FONT *font);

void changeToDisplayCoordinates(int *row, int *col);

void drawBoardByDisplayPiecePositions(UISquare **piecePositions);
void drawPiecesByDisplayPiecePositions(UISquare **piecePositions);
void drawPieceByDisplayPiecePosition(UISquare square);
void drawWhitePawnByDisplayPosition(float x, float y);
void drawBlackPawnByDisplayPosition(float x, float y);
void drawWhiteQueenByDisplayPosition(float x, float y);
void drawBlackQueenByDisplayPosition(float x, float y);
void drawPawnByDisplayPosition(float x, float y, ALLEGRO_COLOR color);
void drawQueenByDisplayPosition(float x, float y, ALLEGRO_COLOR pieceColor, ALLEGRO_COLOR outlineColor);


#endif //CHECKERS_BOARD_PAINTER_H
