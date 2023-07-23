//
// Created by Jj on 22/07/2023.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "input/consoleInputParser.h"
#include "gameEngine/playerMove.h"


extern Player currentPlayer;
extern PlayerMoves playerMoves;
extern Piece board[BOARD_SIZE][BOARD_SIZE];


PlayerMoves getUserChoice() {
    char* input = getUserInput();
    int count;
    Position* moves = parseUserInput(input, &count);
    PlayerMoves playerChoice = translateToPlayerMoves(moves, count);
    free(input);
    free(moves);
    return playerChoice;
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

PlayerMoves translateToPlayerMoves(Position* moves, int count) {
    if (playerMoves.queenCaptureMovesSize > 0) {
        return translateToQueenCaptureMoves(moves, count);
    }
    if (playerMoves.pawnCaptureMovesSize > 0) {
        return translateToPawnCaptureMoves(moves, count);
    }
    if (playerMoves.pieceMovesSize > 0) {
        return translateToPieceMoves(moves);
    }
    return getEmptyPlayerMoves();
}

PlayerMoves translateToQueenCaptureMoves(Position* moves, int count) {
    PlayerMoves playerChoice = initQueenCaptureMoveChoice();
    translateToCaptureMove(moves, count, &playerChoice.queenCaptureMoves[0]);
    return playerChoice;
}

PlayerMoves initQueenCaptureMoveChoice() {
    PlayerMoves playerChoice;
    initPlayerCaptureMoveChoice(&playerChoice.queenCaptureMoves);
    return playerChoice;
}

void initPlayerCaptureMoveChoice(PieceCaptureMoves **playerChoice) {
    *playerChoice = (PieceCaptureMoves*)malloc(sizeof(PieceCaptureMoves));
    (*playerChoice)->captureCollections = (CaptureCollection*)malloc(sizeof(CaptureCollection));
    (*playerChoice)->captureCollections[0].captures = (Position*)malloc(MAX_QUEEN_CAPTURE_MOVES * sizeof(Position));
    (*playerChoice)->toArray = (Position*)malloc(sizeof(Position));
    (*playerChoice)->size = 1;
    (*playerChoice)->allocatedSize = 1;
    (*playerChoice)->captureCollections[0].captureSize = 0;
    (*playerChoice)->captureCollections[0].captureAllocatedSize = MAX_QUEEN_CAPTURE_MOVES;
}

PlayerMoves translateToPawnCaptureMoves(Position* moves, int count) {
    PlayerMoves playerChoice = initPawnCaptureMoveChoice();
    translateToCaptureMove(moves, count, &playerChoice.pawnCaptureMoves[0]);
    return playerChoice;
}

PlayerMoves initPawnCaptureMoveChoice() {
    PlayerMoves playerChoice;
    initPlayerCaptureMoveChoice(&playerChoice.pawnCaptureMoves);
    return playerChoice;
}

void translateToCaptureMove(Position* moves, int count, PieceCaptureMoves *playerChoice) {
    addCaptures(moves, count, playerChoice->captureCollections[0].captures);
    playerChoice->from = moves[0];
    playerChoice->toArray[0] = moves[count-1];
    playerChoice->captureCollections[0].captureSize = count-1;
}

PlayerMoves translateToPieceMoves(Position* moves) {
    PlayerMoves playerChoice = initPlayerMoveChoice();
    playerChoice.pieceMoves[0].from = moves[0];
    playerChoice.pieceMoves[0].to[0] = moves[1];
    return playerChoice;
}

PlayerMoves initPlayerMoveChoice() {
    PlayerMoves playerChoice;
    playerChoice.pieceMovesSize = 1;
    playerChoice.pieceMoves = (PieceMoves*)malloc(playerChoice.pieceMovesSize * sizeof(PieceMoves));
    playerChoice.pieceMoves[0].to = (Position*)malloc(1 * sizeof(Position));

    return playerChoice;
}

void addCaptures(Position *moves, int count, Position* captures) {
    for (int i = 1; i < count; i++) {
        Position moveDirection = getDirection(moves[i-1], moves[i]);
        captures[i-1] = findFirstNonEmptyFromDirection(moves[i-1], moveDirection);
    }
}

Position getDirection(Position start, Position end) {
    int xDiff = end.row - start.row;
    int yDiff = end.col - start.col;

    Position direction;
    direction.row = xDiff / abs(xDiff);
    direction.col = yDiff / abs(yDiff);

    return direction;
}

Position findFirstNonEmptyFromDirection(Position start, Position direction) {
    while (true) {
        start.row += direction.row;
        start.col += direction.col;
        if (board[start.row][start.col] != EMPTY) {
            return start;
        }
    }
}
