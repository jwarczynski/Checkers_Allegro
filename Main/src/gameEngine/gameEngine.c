//
// Created by Jj on 08/07/2023.
//

#include <stdio.h>
#include <stdbool.h>

#include "boardSetup.h"

#include "gameEngine/gameEngine.h"
#include "gameEngine/gameEngineUtil.h"
#include "gameEngine/playerMove.h"
#include "input/consoleInputParser.h"
#include "gameEngine/moveValidator.h"
#include "ui/boardPainter.h"
#include "allegro5/threads.h"

Player currentPlayer;
PlayerMoves playerMoves;
Piece board[BOARD_SIZE][BOARD_SIZE];

extern Position *userPathChoice;
extern int userPathChoiceLength;

extern ALLEGRO_MUTEX* clickMutex;
extern ALLEGRO_COND* clickCond;

extern ALLEGRO_MUTEX *moveExecutedMutex;
extern ALLEGRO_COND *moveExecutedCond;

void runGame() {
    while (true) {
        setupBoard(board);
        currentPlayer = WHITE;

        while (isNotEndOfGame(board)) {
            showBoard(board);
            drawBoard();
            runTurn();
            changePlayer();
        }
        printf("Game over!\n");
        printf("New game? (y/n)\n");
        if (getchar() == 'n') {
            return;
        }
    }
}

void printUserPathChoice() {
    printf("User path choice: ");
    for (int i = 0; i < userPathChoiceLength; i++) {
        printf("(%d, %d) ", userPathChoice[i].row, userPathChoice[i].col);
    }
    printf("\n");
}

void runTurn() {
    PlayerMoves playerChoice;

    initPlayerMoves();
    generatePlayerMoves();
    do {
        al_lock_mutex(clickMutex);
        al_wait_cond(clickCond, clickMutex);
        printUserPathChoice();
        playerChoice = translateToPlayerMoves(userPathChoice, userPathChoiceLength);
        al_unlock_mutex(clickMutex);
        al_signal_cond(moveExecutedCond);
    } while (!checkMoveValidity(playerChoice));
    executeMove(playerChoice);
    deallocatePlayerMovesMemory();
}

void changePlayer() {
    currentPlayer = currentPlayer == WHITE ? BLACK : WHITE;
}

void executeMove(PlayerMoves playerChoice) {
    if (playerMoves.queenCaptureMovesSize > 0) {
        return executeCaptureMove(playerChoice.queenCaptureMoves[0]);
    }
    if (playerMoves.pawnCaptureMovesSize > 0) {
        return executeCaptureMove(playerChoice.pawnCaptureMoves[0]);
    }
    if (playerMoves.pieceMovesSize > 0) {
        return executeNonCaptureMove(playerChoice.pieceMoves[0]);
    }
}

void executeCaptureMove(PieceCaptureMoves pieceCaptureMoves) {
    removeCapturedPieces(pieceCaptureMoves.captureCollections[0]);
    moveFromTo(pieceCaptureMoves.from, pieceCaptureMoves.toArray[0]);
    upgradePawnIfReachedMorphSquare(pieceCaptureMoves.toArray[0]);
}

void upgradePawnIfReachedMorphSquare(Position position) {
    if (board[position.row][position.col] == WHITE_PAWN && position.row == BOARD_SIZE - 1) {
        board[position.row][position.col] = WHITE_QUEEN;
    }
    if (board[position.row][position.col] == BLACK_PAWN && position.row == 0) {
        board[position.row][position.col] = BLACK_QUEEN;
    }
}

void removeCapturedPieces(CaptureCollection captureCollection) {
    for (int i = 0; i < captureCollection.captureSize; i++) {
        board[captureCollection.captures[i].row][captureCollection.captures[i].col] = EMPTY;
    }
}

void moveFromTo(Position from, Position to) {
    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = EMPTY;
}

void executeNonCaptureMove(PieceMoves pieceMove) {
    moveFromTo(pieceMove.from, pieceMove.to[0]);
    upgradePawnIfReachedMorphSquare(pieceMove.to[0]);
}
