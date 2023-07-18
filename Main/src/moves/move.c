////
//// Created by Jj on 07/07/2023.
////
//
//#include <malloc.h>
//#include <stdio.h>
//
//#include "moves/move.h"
//#include "moves/moveUtil.h"
//
//extern Piece board[BOARD_SIZE][BOARD_SIZE];
//extern Player currentPlayer;
//extern PlayerMoves playerMoves;
//
//
//PieceMoves *getMoveFrom(Piece board[BOARD_SIZE][BOARD_SIZE], Position position) {
//    PieceMoves *pieceMoves = malloc(sizeof(PieceMoves));
//
//    if (isWhitePiece(board[position.row][position.col])) {
//        pieceMoves = getWhiteMoves(board, position);
//    } else if (isBlackPiece(board[position.row][position.col])) {
//        pieceMoves = getBlackMoves(board, position);
//    } else {
//        free(pieceMoves);
//        fprintf(stderr, "There is no piece at position (%d, %d)\n", position.row, position.col);
//        return NULL;
//    }
//
//    return pieceMoves;
//}
//
//
//PieceMoves *getBlackMoves(Piece *board[BOARD_SIZE], Position position) {
//    Move *moves = malloc(sizeof(Move) * 4);
//    int moveCount = 0;
//
//    if (board[position.row - 1][position.col - 1] == EMPTY) {
//        moves[moveCount].from = position;
//        moves[moveCount].to.row = position.row - 1;
//        moves[moveCount].to.col = position.col - 1;
//        moveCount++;
//    }
//}
