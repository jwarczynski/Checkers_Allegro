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
#include "ui/display/boardPainter.h"
#include "allegro5/threads.h"

Player currentPlayer;
PlayerMoveCollection playerMoveCollection;
Piece board[BOARD_SIZE][BOARD_SIZE];

extern Move userMoveChoice;

extern ALLEGRO_MUTEX* clickMutex;
extern ALLEGRO_COND* clickCond;

extern ALLEGRO_MUTEX *moveExecutedMutex;
extern ALLEGRO_COND *moveExecutedCond;

void runGame() {
    while (true) {
        setupBoard(board);
        currentPlayer = WHITE;
        drawInterface();

        while (isNotEndOfGame(board)) {
            showBoard(board);
            drawBoard();
            runTurn();
            changePlayer();
        }
        drawInterface();
        printf("Game over!\n");
        printf("New game? (y/n)\n");
        if (getchar() == 'n') {
            return;
        }
    }
}

void printUserPathChoice() {
    printf("User path choice: ");
    for (int i = 0; i < userMoveChoice.positionPath.size; i++) {
        printf("(%d, %d) ", userMoveChoice.positionPath.path[i].row, userMoveChoice.positionPath.path[i].col);
    }
    printf("\n");
}

void runTurn() {
    PlayerMoveCollection userChoice;

    initPlayerMoves();
    generateMoves();

//    TODO: extract to separate function
    bool isUserMoveValid = false;
    while (!isUserMoveValid) {
        waitForUserChoice();
        isUserMoveValid = isMoveValid(userMoveChoice);
        if (!isUserMoveValid) {
            unlockUserInputThread();
        }
    }

PlayerMoves getUserChoiceByInterface() {
    al_lock_mutex(clickMutex);
    al_wait_cond(clickCond, clickMutex);

    printUserPathChoice();
    addCapturesToUserMoveChoice();


}

void unlockUserInputThread() {
    al_unlock_mutex(clickMutex);
    al_signal_cond(moveExecutedCond);

    return playerChoice;
}

void changePlayer() {
    currentPlayer = currentPlayer == WHITE ? BLACK : WHITE;
}

void executeMove(Move move) {
    removeCapturedPieces(move.captureCollection);
    moveFromTo(move.positionPath.path[0], move.positionPath.path[move.positionPath.size - 1]);
    upgradePawnIfReachedMorphSquare(move.positionPath.path[move.positionPath.size - 1]);
}

void executeIntermediateMove(Position from, Position to, Position capture) {
    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = EMPTY;
    board[capture.row][capture.col] = EMPTY;
}

void executeLastIntermediateMove(Position from, Position to, Position capture) {
    executeIntermediateMove(from, to, capture);
    upgradePawnIfReachedMorphSquare(to);
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
    for (int i = 0; i < captureCollection.size; i++) {
        board[captureCollection.captures[i].row][captureCollection.captures[i].col] = EMPTY;
    }
}

void moveFromTo(Position from, Position to) {
    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = EMPTY;
}

void resetUserMoveChoice() {
    userMoveChoice.positionPath.size = 0;
    userMoveChoice.captureCollection.size = 0;
}
