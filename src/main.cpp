#include <cctype>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <header.h>
#include <warcaby.h>

void draw_available_pawns_field(int i, int j, char **board, char my_pawn, char opp_pawn, ALLEGRO_BITMAP *buffer,
                                int priority,
                                struct field beat[][8], struct field mv[][8], struct queen q_tab[][8],
                                struct q_move q_mv[][8]) {

    al_set_target_bitmap(buffer);
    if (board[i][j] == my_pawn) {
        if (priority == 1)
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
        else if (priority == 2) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            for (int k = 0; k < 4; k++) {
                if (beat[i][j].next[k])
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 200, 85));
            }
        } else {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            check_move_possibilities(board, i, j, &mv[i][j], my_pawn);
            for (int k = 0; k < 4; k++) {
                if (mv[i][j].next[k])
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 200, 85));
            }
        }
        if (my_pawn == 'a') al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        else
            al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
    } else if (board[i][j] == toupper(my_pawn)) {
        if (priority == 1) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            queen_beat_possibilities(board, my_pawn, opp_pawn, &q_tab[i][j], i, j);
            for (int k = 0; k < 9; k++) {
                if (q_tab[i][j].next[k]) {
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 200, 85));
                    break;
                }
            }
        } else if (priority == 2)
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
        else {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            q_moves(board, my_pawn, opp_pawn, &q_mv[i][j], i, j);
            for (int k = 0; k < 16; k++) {
                if (q_mv[i][j].next[k]) {
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 200, 85));
                }
            }
        }
        if (my_pawn == 'a') al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        else
            al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
        al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
    } else if (board[i][j] == ' ')
        al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
    else if (board[i][j] == '-')
        al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(226, 223, 211));
    else if (board[i][j] == toupper(opp_pawn)) {
        al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
        if (my_pawn == 'a') al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
        else
            al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
    } else if (board[i][j] == opp_pawn) {
        al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
        if (opp_pawn == 'a') al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        else
            al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
    }
}

void draw_available_pawns(char **board, char my_pawn, char opp_pawn, ALLEGRO_BITMAP *buffer, int priority,
                          struct field beat[][8], struct field mv[][8], struct queen q_tab[][8],
                          struct q_move q_mv[][8]) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            draw_available_pawns_field(i, j, board, my_pawn, opp_pawn, buffer, priority, beat, mv, q_tab, q_mv);
        }
    }
}

void mark_available_pawn(int *x, int *y, ALLEGRO_BITMAP *buffer) {

    ALLEGRO_COLOR read_color = al_get_pixel(buffer, *x * 80 + 5, *y * 80 + 5);
    ALLEGRO_COLOR available = al_map_rgb(119, 200, 85);
    while (!(read_color.r == available.r && read_color.g == available.g && read_color.b == available.b)) {
        if (*x >= 7) {
            *x = 0;
            if (*y >= 7)
                *y = 0;
            else
                *y += 1;
        } else
            *x += 1;
        read_color = al_get_pixel(buffer, *x * 80 + 5, *y * 80 + 5);
    }
}

void draw_available_field(int x, int y, int i, int j, char **board, char my_pawn, char opp_pawn, ALLEGRO_BITMAP *buffer,
                          int priority,
                          struct field beat[][8], struct field mv[][8], struct queen q_tab[][8],
                          struct q_move q_mv[][8]) {

    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
    if (priority == 1) {
        if (board[x][y] == toupper(my_pawn)) {
            queen_beat_possibilities(board, my_pawn, opp_pawn, &q_tab[x][y], x, y);
            if (can_here_beat_q(&q_tab[x][y], i, j))
                al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                         al_map_rgb(119, 200, 85));
        }

        if (board[i][j] == '-')
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(226, 223, 211));
            //else if(board[i][j] == ' ')
            //al_draw_filled_rectangle(j*80,(7-i)*80,j*80+80,(7-i)*80+80,al_map_rgb(119,148,85));
        else if (board[i][j] == opp_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        } else if (board[i][j] == toupper(opp_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        } else if (board[i][j] == my_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
        } else if (board[i][j] == toupper(my_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        }
    } else if (priority == 2) {
        if (board[x][y] == my_pawn) {
            check_beat_possibilities(board, &beat[x][y], x, y, my_pawn);
            if (can_here_beat(&beat[x][y], i, j)) {
                al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                         al_map_rgb(119, 200, 85));
            }
        }


        if (board[i][j] == '-')
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(226, 223, 211));
            //else if(board[i][j] == ' ')
            //al_draw_filled_rectangle(j*80,(7-i)*80,j*80+80,(7-i)*80+80,al_map_rgb(119,148,85));
        else if (board[i][j] == opp_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        } else if (board[i][j] == toupper(opp_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        } else if (board[i][j] == my_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
        } else if (board[i][j] == toupper(my_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        }


    } else {
        if (board[x][y] == my_pawn) {
            check_move_possibilities(board, x, y, &mv[x][y], my_pawn);
            if (can_here_move(&mv[x][y], i, j))
                al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                         al_map_rgb(119, 200, 85));
        } else if (board[x][y] == toupper(my_pawn)) {
            q_moves(board, my_pawn, opp_pawn, &q_mv[x][y], x, y);
            if (can_q_here_move(&q_mv[x][y], i, j))
                al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                         al_map_rgb(119, 200, 85));
        }


        if (board[i][j] == '-')
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(226, 223, 211));
            //else if(board[i][j] == ' ')
            //al_draw_filled_rectangle(j*80,(7-i)*80,j*80+80,(7-i)*80+80,al_map_rgb(119,148,85));
        else if (board[i][j] == opp_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
        } else if (board[i][j] == toupper(opp_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (opp_pawn == 'b')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        } else if (board[i][j] == my_pawn) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
        } else if (board[i][j] == toupper(my_pawn)) {
            al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80, al_map_rgb(119, 148, 85));
            if (my_pawn == 'a')
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
            al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
        }
    }
}


void
draw_available_fields(int x, int y, char **board, char my_pawn, char opp_pawn, ALLEGRO_BITMAP *buffer, int priority,
                      struct field beat[][8], struct field mv[][8], struct queen q_tab[][8], struct q_move q_mv[][8]) {

    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            draw_available_field(x, y, i, j, board, my_pawn, opp_pawn, buffer, priority, beat, mv, q_tab, q_mv);
        }
    }
};

void draw_board(char **board, ALLEGRO_BITMAP *buffer) {

    al_set_target_bitmap(buffer);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case ' ':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 148, 85));
                    break;
                case '-':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(226, 223, 211));
                    break;
                case 'a':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 148, 85));
                    al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
                    break;
                case 'b':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 148, 85));
                    al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
                    break;
                case 'A':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 148, 85));
                    al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(255, 255, 255));
                    al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
                    break;
                case 'B':
                    al_draw_filled_rectangle(j * 80, (7 - i) * 80, j * 80 + 80, (7 - i) * 80 + 80,
                                             al_map_rgb(119, 148, 85));
                    al_draw_filled_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(1, 1, 1));
                    al_draw_circle(j * 80 + 40, (7 - i) * 80 + 40, 20, al_map_rgb(30, 200, 30), 5);
                    break;
            }
        }
    }
}

int move_priority(char **board, char my_pawn, char opp_pawn, struct field beat[][8], struct field mv[][8],
                  struct queen q_tab[][8], struct q_move q_mv[][8]) {

    if (any_q_beat(q_tab, my_pawn, opp_pawn, board)) return 1;
    if (any_beat(beat, my_pawn, board)) return 2;
    return 3;
}

int main() {

    int x1, x2, y1, y2;
    char PAWN1 = 'b', PAWN2 = 'a';

    struct field tab[8][8];
    struct field tab_m[8][8];
    struct queen q_tab[8][8];
    struct q_move q_m[8][8];
    char name[] = "../assets/board.txt";
    char *board[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new char[8];
    }
    read_board(board, name);
    show_board(board);


    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *buffer = NULL;

    al_init();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_FONT *font = al_load_font("../assets/font.otf", 100, NULL);

    display = al_create_display(640, 640);
    buffer = al_create_bitmap(640, 640);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyState;
    clean(tab, tab_m, q_tab, q_m);
    al_start_timer(timer);
    bool right_arrow = false;
    bool pressed_enter = false;
    int enter = 0;
    bool next_move = true;
    int priority;
    int x_pos = 0;
    int y_pos = 0;

    while (true) {

        if (next_move) {
            next_move = false;
            priority = move_priority(board, PAWN1, PAWN2, tab, tab_m, q_tab, q_m);
            draw_available_pawns(board, PAWN1, PAWN2, buffer, priority, tab, tab_m, q_tab, q_m);
            al_set_target_bitmap(al_get_backbuffer(display));
            mark_available_pawn(&x_pos, &y_pos, buffer);
            al_draw_bitmap(buffer, 0, 0, NULL);
            al_draw_rectangle(x_pos * 80, y_pos * 80, x_pos * 80 + 80, y_pos * 80 + 80, al_map_rgb(200, 10, 0), 2);
            al_flip_display();
        }


        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            al_get_keyboard_state(&keyState);
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                right_arrow = true;
            else if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)) {
                pressed_enter = true;
            }
        }
        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (right_arrow) {
                right_arrow = false;
                x_pos += 1;
                mark_available_pawn(&x_pos, &y_pos, buffer);
                al_draw_bitmap(buffer, 0, 0, NULL);
                al_draw_rectangle(x_pos * 80, y_pos * 80, x_pos * 80 + 80, y_pos * 80 + 80, al_map_rgb(200, 10, 0), 2);
                al_flip_display();
            } else if (pressed_enter) {
                pressed_enter = false;
                enter++;
                if (enter == 1) {
                    draw_available_fields((7 - y_pos), x_pos, board, PAWN1, PAWN2, buffer, priority, tab, tab_m, q_tab,
                                          q_m);// trzeba podaæ 7-y_pos x_pos
                    al_set_target_bitmap(al_get_backbuffer(display));
                    al_draw_bitmap(buffer, 0, 0, NULL);
                    x1 = 7 - y_pos;
                    y1 = x_pos;
                    x_pos = 0;
                    y_pos = 0;
                    mark_available_pawn(&x_pos, &y_pos, buffer);
                    al_draw_rectangle(x_pos * 80, y_pos * 80, x_pos * 80 + 80, y_pos * 80 + 80, al_map_rgb(200, 10, 0),
                                      2);
                    al_flip_display();
                } else if (enter == 2) {
                    enter = 0;
                    x2 = 7 - y_pos;
                    y2 = x_pos;
                    is_correct(board, PAWN1, PAWN2, x1, y1, x2, y2, tab, tab_m, q_tab, q_m);
                    x_pos = 0;
                    y_pos = 0;
                    next_move = true;
                    clean(tab, tab_m, q_tab, q_m);
                    swap_chars(&PAWN1, &PAWN2);
                    if (is_end_of_game(board, PAWN1)) {
                        next_move = false;
                        draw_board(board, buffer);
                        al_set_target_bitmap(al_get_backbuffer(display));
                        al_draw_bitmap(buffer, 0, 0, NULL);
                        al_draw_text(font, al_map_rgb(111, 115, 180), 320, 320, ALLEGRO_ALIGN_CENTER, "END OF GAME");
                        al_flip_display();
                    }
                }
            }

        }

    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_bitmap(buffer);
    al_destroy_font(font);
    al_destroy_event_queue(queue);

    return 0;
}
