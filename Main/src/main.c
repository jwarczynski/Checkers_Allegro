//
// Created by Jj on 07/07/2023.
//

#include <allegro5/allegro.h>
#include <pthread.h>
#include <stdio.h>

#include "gameEngine/gameEngine.h"
#include "main.h"
#include "ui/eventHandler.h"
#include "ui/uiInitializer.h"

ALLEGRO_MUTEX* clickMutex;
ALLEGRO_COND* clickCond;

ALLEGRO_MUTEX *moveExecutedMutex;
ALLEGRO_COND *moveExecutedCond;

int main() {

    initSynchronizationObjects();
    initUI();

    pthread_t gameThreadID;
    int gameThreadCreationResult = pthread_create(&gameThreadID, NULL, (void *(*)(void *)) runGame, NULL);
    if (gameThreadCreationResult != 0) {
        fprintf(stderr, "Failed to create game thread: %d\n", gameThreadCreationResult);
        return 1;
    }

    pthread_t eventHandlingThreadID;
    int eventHandlingThreadCreationResult = pthread_create(&eventHandlingThreadID, NULL, eventHandler, NULL);
    if (eventHandlingThreadCreationResult != 0) {
        fprintf(stderr, "Failed to create event-handling thread: %d\n", eventHandlingThreadCreationResult);
        return 1;
    }

    pthread_join(gameThreadID, NULL);
    pthread_join(eventHandlingThreadID, NULL);

    cleanupSynchronizationObjects();
    runGame();

    return 0;
}

void initSynchronizationObjects() {
    clickMutex = al_create_mutex();
    clickCond = al_create_cond();

    moveExecutedMutex = al_create_mutex();
    moveExecutedCond = al_create_cond();
}

void cleanupSynchronizationObjects() {
    al_destroy_mutex(clickMutex);
    al_destroy_cond(clickCond);
}
