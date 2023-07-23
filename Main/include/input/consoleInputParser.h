//
// Created by Jj on 22/07/2023.
//

#ifndef CHECKERS_CONSOLE_INPUT_PARSER_H
#define CHECKERS_CONSOLE_INPUT_PARSER_H

#include "types.h"
#include <stdbool.h>


PlayerMoves getUserChoice();
char* getUserInput();
Position* parseUserInput(char* input, int *countInOut);
bool parsePositionString(const char* input, Position* position);

PlayerMoves translateToPlayerMoves(Position* moves, int count);
PlayerMoves translateToPieceMoves(Position* moves);
PlayerMoves translateToQueenCaptureMoves(Position* moves, int count);
PlayerMoves translateToPawnCaptureMoves(Position* moves, int count);
void translateToCaptureMove(Position* moves, int count, PieceCaptureMoves *playerChoice);

PlayerMoves initPlayerMoveChoice();
PlayerMoves initQueenCaptureMoveChoice();
PlayerMoves initPawnCaptureMoveChoice();
void initPlayerCaptureMoveChoice(PieceCaptureMoves **playerChoice);

Position getDirection(Position start, Position end);
Position findFirstNonEmptyFromDirection(Position start, Position direction);
void addCaptures(Position *moves, int count, Position* captures);

#endif //CHECKERS_CONSOLE_INPUT_PARSER_H
