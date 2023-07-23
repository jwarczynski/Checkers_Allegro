//
// Created by Jj on 23/07/2023.
//

#include <stdio.h>
#include <unistd.h>
#include "ui/eventHandler.h"
#include "ui/uiState.h"
#include "ui/uiInitializer.h"
#include "ui/eventHandlerUtil.h"
#include "gameEngine/moveValidator.h"

extern UI ui;

extern ALLEGRO_MUTEX* clickMutex;
extern ALLEGRO_COND* clickCond;

extern ALLEGRO_MUTEX *moveExecutedMutex;
extern ALLEGRO_COND *moveExecutedCond;

Position *userPathChoice = NULL;
int userPathChoiceLength = 0;

void* eventHandler(void* arg) {
    userPathChoice = malloc(sizeof(Position) * 10);

    while (1) {
        al_lock_mutex(moveExecutedMutex);

        ALLEGRO_EVENT event;
        al_wait_for_event(ui.queue, &event);
        handleEvent(event);
    }
}

void handleIncomingEvents() {
    if (userPathChoice == NULL) {
        userPathChoice = malloc(sizeof(Position) * 10);
    }
    ALLEGRO_EVENT event;
    al_wait_for_event(ui.queue, &event);
    handleEvent(event);
}

void handleEvent(ALLEGRO_EVENT event) {
    switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            closeApp();
        case ALLEGRO_EVENT_KEY_DOWN:
            handleKeyDown(event);
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            handleMouseClick(event);
        default:
            return;
    }
}

void closeApp() {
    destroyUI();
    exit(0);
}

void handleMouseClick(ALLEGRO_EVENT event) {
    if (isInsideBoard(event.mouse.x, event.mouse.y)) {
        handleBoardClick(event);
    }
    handleNonBoardCLick(event);
}

void handleKeyDown(ALLEGRO_EVENT event) {
    switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            return resetMoveChoice();
        default:
            return;
    }
}

void handleBoardClick(ALLEGRO_EVENT event) {
    static Position lastClick = {-1, -1};

    if (event.mouse.x == -1) {
        printf("resetting\n");
        return resetSelectingMovePath(&lastClick);
    }

    Position click = translateToBoardPosition(event.mouse.x, event.mouse.y);
    if (arePointsEqual(click, lastClick)) {
        printf("same click\n");
        al_signal_cond(clickCond);
        al_wait_cond(moveExecutedCond, moveExecutedMutex);
        return resetSelectingMovePath(&lastClick);
    }
    userPathChoice[userPathChoiceLength++] = click;
    lastClick = click;
}

void handleNonBoardCLick(ALLEGRO_EVENT event) {

}

void resetSelectingMovePath(Position *lastClick) {
    *lastClick = (Position) {-1, -1};
    userPathChoiceLength = 0;
}

void resetMoveChoice() {
    ALLEGRO_EVENT event;
    event.mouse.x = -1;
    handleBoardClick(event);
}