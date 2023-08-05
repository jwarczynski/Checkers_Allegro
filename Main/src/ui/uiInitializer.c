//
// Created by Jj on 23/07/2023.
//

#include "ui/uiInitializer.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "ui/uiState.h"
#include "ui/display/UIConstants.h"
#include "types.h"

UI ui;
static const char *fontPath = "../assets/Roboto_Mono/static/RobotoMono-Bold.ttf";

void initUI() {
    initAllegro();
    initAllegroAddons();
    registerEvents();
    loadFonts(fontPath);
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
    int displayWidth = LEFT_PANEL_WIDTH + BOARD_SIZE * SQUARE_SIZE + RIGHT_PANEL_WIDTH;
    int displayHeight = TOP_PANEL_HEIGHT + BOARD_SIZE * SQUARE_SIZE + BOTTOM_PANEL_HEIGHT;
    ui.display = al_create_display(displayWidth, displayHeight);
    ui.buffer = al_create_bitmap(displayWidth, displayHeight);
    ui.queue = al_create_event_queue();
}

void registerEvents() {
    al_register_event_source(ui.queue, al_get_keyboard_event_source());
    al_register_event_source(ui.queue, al_get_display_event_source(ui.display));
    al_register_event_source(ui.queue, al_get_mouse_event_source());
}

void loadFonts(const char *path) {
    ui.coordinateFont = al_load_font(path, 30, 0);
    ui.menuFont = al_load_font(path, 40, 0);
}

void destroyUI() {
    al_destroy_display(ui.display);
    al_uninstall_keyboard();
    al_destroy_bitmap(ui.buffer);
    al_destroy_font(ui.coordinateFont);
    al_destroy_font(ui.menuFont);
    al_destroy_event_queue(ui.queue);
}