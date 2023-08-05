//
// Created by Jj on 15/07/2023.
//

#include "moves/moves/queenMove.h"
#include "moves/moveUtil.h"
#include "moves/move.h"


extern Piece board[BOARD_SIZE][BOARD_SIZE];


void generateQueenMovesFrom(Position position) {
    generateAllDirectionsMovesFrom(position, generateQueenMovesInDirection);
}


void generateQueenMovesInDirection(Position from, Position direction) {
    Position to = {from.row + direction.row, from.col + direction.col};
    while (isOnBoard(to) && isEmpty(board, to)) {
        Move move;
        fillNonCaptureMove(&move, from, to);
        addMoveToPlayerMoves(move);
        changePosition(&to, direction.row, direction.col);
    }
}
