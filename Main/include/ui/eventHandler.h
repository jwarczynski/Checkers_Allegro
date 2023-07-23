//
// Created by Jj on 23/07/2023.
//

#ifndef CHECKERS_EVENT_HANDLER_H
#define CHECKERS_EVENT_HANDLER_H

#include "allegro5/events.h"
#include "types.h"

// INTERFACE
void handleIncomingEvents();
void* eventHandler(void* arg);

// implementation
void handleEvent(ALLEGRO_EVENT event);

void handleMouseClick(ALLEGRO_EVENT event);
void handleKeyDown(ALLEGRO_EVENT event);

void handleBoardClick(ALLEGRO_EVENT event);
void handleNonBoardCLick(ALLEGRO_EVENT event);

void closeApp();

void resetSelectingMovePath(Position *lastClick);
void resetMoveChoice();

#endif //CHECKERS_EVENT_HANDLER_H
