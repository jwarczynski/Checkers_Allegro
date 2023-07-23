//
// Created by Jj on 23/07/2023.
//

#ifndef CHECKERS_UI_STATE_H
#define CHECKERS_UI_STATE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct ui {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *buffer;
    ALLEGRO_FONT *font;
} UI;

#endif //CHECKERS_UI_STATE_H
