//
// Created by Jj on 07/07/2023.
//

#ifndef CHECKERS_TYPES_H
#define CHECKERS_TYPES_H

#define BOARD_SIZE 8
#define MAX_QUEEN_CAPTURE_MOVES 20
#define ALLOCATION_STEP_SIZE 10

#define INITIAL_PLAYER_MOVES_CAPACITY 20
#define INITIAL_CAPTURES_CAPACITY 10
#define INITIAL_PATH_SIZE 10

typedef enum Piece {
    EMPTY,
    WHITE_PAWN,
    BLACK_PAWN,
    WHITE_QUEEN,
    BLACK_QUEEN,
} Piece;

typedef enum PieceType {
    PAWN,
    QUEEN,
} PieceType;

typedef struct Position {
    int row;
    int col;
} Position;

typedef struct PieceMoves {
    Position from;
    Position *to;

    int allocatedSize;
    int size;
} PieceMoves;

typedef struct CaptureCollection {
    Position *captures;
    int size;
    int allocatedSize;
} CaptureCollection;

typedef struct PieceCaptureMoves {
    Position from;
    Position *toArray;

    CaptureCollection *captureCollections;

    int size;
    int allocatedSize;
} PieceCaptureMoves;


typedef struct PlayerMoves {
    PieceCaptureMoves *queenCaptureMoves;
    PieceCaptureMoves *pawnCaptureMoves;
    PieceMoves *pieceMoves;

    int queenCaptureMovesAllocatedSize;
    int pawnCaptureMovesAllocatedSize;
    int pieceMovesAllocatedSize;

    int queenCaptureMovesSize;
    int pawnCaptureMovesSize;
    int pieceMovesSize;
} PlayerMoves;

typedef enum Player {
    WHITE,
    BLACK,
} Player;

typedef struct UISquare {
    float x;
    float y;
    Piece piece;
} UISquare;

typedef struct PositionPath{
    Position *path;
    int size;
    int allocatedSize;
} PositionPath;

typedef struct Move {
    PositionPath positionPath;
    CaptureCollection captureCollection;
} Move;

typedef struct PlayerMoveCollection {
    Move *moves;
    int size;
    int allocatedSize;
} PlayerMoveCollection;

typedef void (*PieceMoveStrategy)(Position start, Position direction);

#endif //CHECKERS_TYPES_H
