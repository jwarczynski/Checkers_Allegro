//
// Created by Jj on 28/07/2023.
//

#include "ui/display/animations/moveAnimation.h"
#include "globals.h"
#include "ui/uiState.h"
#include "ui/display/boardPainter.h"
#include "ui/display/UIConstants.h"
#include "moves/moveUtil.h"
#include "gameEngine/gameEngine.h"

extern UI ui;

const float ANIMATION_SPEED = 0.05f;
#define ANIMATION_FPS 60


void animateMove(Move move) {
    for (int i = 0; i < move.positionPath.size - 1; ++i) {
        Position capture = move.captureCollection.size - i > 0 ? move.captureCollection.captures[i] : getEmptyPosition();
        animateIntermediateMove(move.positionPath.path[i], move.positionPath.path[i + 1], capture);
    }
    upgradePawnIfReachedMorphSquare(move.positionPath.path[move.positionPath.size - 1]);

}

void animateIntermediateMove(Position from, Position to, Position capturedPiecePosition) {
//    TODO: divide this function into smaller functions
    UISquare **piecePositions = translateToDisplayPositions();
    UISquare *animatingPieceSquare = &piecePositions[from.row][from.col];
    UISquare *destinationSquare = &piecePositions[to.row][to.col];
    translateToDisplayPosition(destinationSquare, to.row, to.col);

    float startX = animatingPieceSquare->x;
    float startY = animatingPieceSquare->y;

    float animationProgress = 0;

    ALLEGRO_TIMER* animationTimer = al_create_timer(1.0 / ANIMATION_FPS);
    ALLEGRO_EVENT_QUEUE *animationQueue = al_create_event_queue();
    al_register_event_source(animationQueue, al_get_timer_event_source(animationTimer));
    al_start_timer(animationTimer);

    while (animationProgress < 1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(animationQueue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER) {
            animationProgress += ANIMATION_SPEED;
            animatingPieceSquare->x = lerp(startX, destinationSquare->x, animationProgress);
            animatingPieceSquare->y = lerp(startY, destinationSquare->y, animationProgress);
            drawBoardByDisplayPiecePositions(piecePositions);
        }
    }

    destinationSquare->piece = animatingPieceSquare->piece;
//    animatingPieceSquare->x = destinationSquare->x;
    executeIntermediateMove(from, to, capturedPiecePosition);
    drawBoardByDisplayPiecePositions(piecePositions);

    al_destroy_event_queue(animationQueue);
    al_destroy_timer(animationTimer);
}

// Helper function for linear interpolation
float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

UISquare **translateToDisplayPositions() {
    UISquare **piecePositions = malloc(sizeof(UISquare *) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        piecePositions[i] = malloc(sizeof(UISquare) * BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++) {
           translateToDisplayPosition(&piecePositions[i][j], i, j);
           piecePositions[i][j].piece = board[i][j];
        }
    }
    return piecePositions;
}

void translateToDisplayPosition(UISquare *piece, int row, int col) {
    float x, y;
    changeToDisplayCoordinates(&row, &col);
    defineSquareMiddle(&x, &y, row, col);

    piece->x = x;
    piece->y = y;
}

void defineSquareMiddle(float *x, float *y, int row, int col) {
    *x = (float) col * SQUARE_SIZE + LEFT_PANEL_WIDTH + (float) SQUARE_SIZE / 2;
    *y = (float) row * SQUARE_SIZE + TOP_PANEL_HEIGHT + (float) SQUARE_SIZE / 2;
}


