//
// Created by Jj on 21/07/2023.
//

#ifndef CHECKERS_QUEEN_MOVE_TEST_H
#define CHECKERS_QUEEN_MOVE_TEST_H

void shouldYield7MovesOnOneDiagonal();
void shouldYieldNoMoves();
void shouldYield2MovesOnEachDiagonalOpponentStop();
void shouldYield2MovesOnEachDiagonalOwnPawnStop();
void shouldYield2MovesOnEachDiagonalOwnQueenStop();
void shouldYield2MovesOnEachDiagonalOpponentQueenStop();

void shouldYield2MovesOnEachDiagonalPieceStop(Piece piece);

#endif //CHECKERS_QUEEN_MOVE_TEST_H

