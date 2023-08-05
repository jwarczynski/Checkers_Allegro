//
// Created by Jj on 22/07/2023.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "input/consoleInputParser.h"
#include "globals.h"
#include "moves/moveUtil.h"
#include "gameEngine/moveValidator.h"

PlayerMoves getUserChoice() {
    char* input = getUserInput();
    int count;
    Position* moves = parseUserInput(input, &count);
    free(input);
    free(moves);
}

char* getUserInput() {
    const int MAX_INPUT_LENGTH = 100;
    char* input = (char*)malloc(MAX_INPUT_LENGTH * sizeof(char));

    printf("Enter your moves. Terminate input with '#' character and press Enter.\n");
    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        exit(EXIT_FAILURE);
    }
    return input;
}

Position* parseUserInput(char *input, int *countInOut) {
    int capacity = 10;
    int count = 0;
    char *inputCopy = strdup(input);
    Position* moves = (Position*)malloc(capacity * sizeof(Position));
    char* token = strtok(inputCopy, " ");

    while (token != NULL && token[0] != '#') {
        Position movePosition;
        if (parsePositionString(token, &movePosition)) {
            if (count == capacity) {
                capacity *= 2;
                moves = (Position*)realloc(moves, capacity * sizeof(Position));
            }

            moves[count] = movePosition;
            count++;
        } else {
            printf("Invalid input: %s. Skipping.\n", token);
        }

        // Move to the next token.
        token = strtok(NULL, " ");
    }

    *countInOut = count;
    return moves;
}

bool parsePositionString(const char* input, Position* position) {
    if (sscanf(input, "%1[A-Z]%d", (char*)&position->col, &position->row) != 2) {
        return false; // Parsing failed.
    }

    position->col -= 'A'; // Convert from letter to 0-based index.
    position->row -= 1; // Convert from letter to 0-based index.

    return true; // Parsing successful.
}



//    TODO: move to converter.c

void addCapturesToUserMoveChoice() {
    for (int i = 1; i < userMoveChoice.positionPath.size; ++i) {
        addCaptureIfOpponentOnPath(userMoveChoice.positionPath.path[i-1], userMoveChoice.positionPath.path[i]);
    }
}

void addCaptureIfOpponentOnPath(Position start, Position end) {
    Position firstOpponentPiecePosition = findFirstNonEmptyPiecePosition(start, end);
    if (isNotNullPosition(firstOpponentPiecePosition)) {
        addCaptureToUserMoveChoice(firstOpponentPiecePosition);
    }
}

Position findFirstNonEmptyPiecePosition(Position start, Position end) {
    Position direction = getDirection(start, end);
    while (arePointsDifferent(start, end) && isOnBoard(start)) {
        start.row += direction.row;
        start.col += direction.col;
        if (isOpponentPiece(board[start.row][start.col])) {
            return start;
        }
    }
    return getNullPosition();
}

Position getDirection(Position start, Position end) {
    int xDiff = end.row - start.row;
    int yDiff = end.col - start.col;

    Position direction;
    direction.row = xDiff / abs(xDiff);
    direction.col = yDiff / abs(yDiff);

    return direction;
}

void addCaptureToUserMoveChoice(Position capture) {
    userMoveChoice.captureCollection.captures[userMoveChoice.captureCollection.size++] = capture;
}

