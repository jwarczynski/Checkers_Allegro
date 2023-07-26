//
// Created by Jj on 26/07/2023.
//

#include <pthread.h>
#include <stdio.h>
#include "threadManager.h"
#include "allegro5/threads.h"
#include "ui/uiInitializer.h"
#include "gameEngine/gameEngine.h"
#include "ui/eventHandler.h"

ALLEGRO_MUTEX* clickMutex;
ALLEGRO_COND* clickCond;

ALLEGRO_MUTEX *moveExecutedMutex;
ALLEGRO_COND *moveExecutedCond;

void start() {

    initSynchronizationObjects();
    initUI();

    pthread_t gameThreadID;
    int gameThreadCreationResult = pthread_create(&gameThreadID, NULL, (void *(*)(void *)) runGame, NULL);
    if (gameThreadCreationResult != 0) {
        fprintf(stderr, "Failed to create game thread: %d\n", gameThreadCreationResult);
        closeApp();
    }

    pthread_t eventHandlingThreadID;
    int eventHandlingThreadCreationResult = pthread_create(&eventHandlingThreadID, NULL, eventHandler, NULL);
    if (eventHandlingThreadCreationResult != 0) {
        fprintf(stderr, "Failed to create event-handling thread: %d\n", eventHandlingThreadCreationResult);
        closeApp();
    }

    pthread_join(gameThreadID, NULL);
    pthread_join(eventHandlingThreadID, NULL);

    cleanupSynchronizationObjects();
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
