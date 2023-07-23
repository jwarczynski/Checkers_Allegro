//
// Created by Jj on 23/07/2023.
//

#include "ui/uiInitializer.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "ui/uiState.h"

UI ui;
static const char *fontPath = "../assets/font.otf";

void initUI() {
    initAllegro();
    initAllegroAddons();
    registerEvents();
    loadFont(fontPath);
}

void initAllegro() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
}

void initAllegroAddons() {
    ui.display = al_create_display(640, 640);
    ui.buffer = al_create_bitmap(640, 640);
    ui.queue = al_create_event_queue();
    ui.timer = al_create_timer(1.0 / 60);
}

void registerEvents() {
    al_register_event_source(ui.queue, al_get_keyboard_event_source());
    al_register_event_source(ui.queue, al_get_display_event_source(ui.display));
    al_register_event_source(ui.queue, al_get_timer_event_source(ui.timer));
    al_register_event_source(ui.queue, al_get_mouse_event_source());

    al_start_timer(ui.timer);
}

void loadFont(const char *path) {
    ui.font = al_load_font(path, 100, 0);
}

void destroyUI() {
    al_destroy_display(ui.display);
    al_uninstall_keyboard();
    al_destroy_timer(ui.timer);
    al_destroy_bitmap(ui.buffer);
    al_destroy_font(ui.font);
    al_destroy_event_queue(ui.queue);
}