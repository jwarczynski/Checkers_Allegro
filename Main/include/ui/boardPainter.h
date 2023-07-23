//
// Created by Jj on 23/07/2023.
//

#ifndef CHECKERS_BOARD_PAINTER_H
#define CHECKERS_BOARD_PAINTER_H

#include "allegro5/color.h"

// INTERFACE
void drawBoard();

// implementation
void drawSquares();
void drawRow(int row);
void drawSquare(int row, int column, ALLEGRO_COLOR color);

void drawPieces();
void drawPiece(int row, int col);

ALLEGRO_COLOR getColor(int row, int col);


void drawWhitePawn(int row, int col);
void drawBlackPawn(int row, int col);
void drawWhiteQueen(int row, int col);
void drawBlackQueen(int row, int col);
void drawPawn(int row, int col, ALLEGRO_COLOR color);
void drawQueen(int row, int col, ALLEGRO_COLOR color);

void drawPawnCircle(int row, int col, ALLEGRO_COLOR color);
void drawQueenCircle(int row, int col, ALLEGRO_COLOR color);
void drawFilledCircle(int row, int col, float radius, ALLEGRO_COLOR color);

void changeToDisplayCoordinates(int *row, int *col);

#endif //CHECKERS_BOARD_PAINTER_H
