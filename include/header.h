#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//struct killed{
//
//    int x, y;
//    struct killed* next;
//};
//struct field{
//
//    int x, y, length;
//    struct killed* killed_pawns;
//    struct field* next[4];
//};
//struct q_killed{
//
//  int x, y;
//  struct q_killed* next;
//};
//struct queen{
//
//    int x, y;
//    struct queen* next[9];
//    struct q_killed* killed_by_q;
//};
//struct q_move{
//
//    int x, y;
//    struct q_move* next[16];
//};

int move_priority(char** board, char my_pawn, char opp_pawn, struct field beat[][8], struct field mv[][8], struct queen q_tab[][8], struct q_move q_mv[][8]);
void delete_board(char** board);
void copy_board(char** board, char** copied);
void catapult(char** board, int x, int y);
void move_pawn(char** board, char pawn, int x1, int y1, int x2, int y2);
void zeruj_field(struct field* field);
bool read_coordinates(int* x1, int* y1, int* x2, int* y2);
void show_board(char** board);
void read_board(char** board, char* name);
bool is_free(char** board, int x, int y);
bool is_opponent(char** board, int x, int y, char pawn);
bool is_on_board(int x, int y);
void clean(struct field tab[][8], struct field mov[][8], struct queen qt[][8], struct q_move qm[][8]);
bool is_possible_beat(char** board, int x, int y, int x_offset, int y_offset, char pawn);
struct killed* copy_kill(struct killed* k1, struct killed* k2);
struct field* add_to_tree(char** board, char pawn, struct field* dest, int x, int y, int x_offset, int y_offset, struct killed* prev);
struct field* check_beat_possibilities_util(char** board, int x, int y, int of1, int of2, char pawn, struct field* dest, struct field* tmp, int id);
struct field* check_beat_possibilities(char** board, struct field* dest, int x, int y, char pawn);
void show_posibilities(struct field* field);
struct field* check_move_possibilities(char** board, int x, int y, struct field* dest, char pawn);
bool any_beat_util(struct field* field);
bool any_beat(struct field tab[][8], char pawn, char** board);
bool any_q_beat_util(struct queen* field);
bool any_q_beat(struct queen tab[][8], char pawn, char opp_pawn, char** board);
bool can_here_move(struct field* field, int x, int y);
bool is_end_of_game(char** board, char opp_pawn);
struct field* can_here_beat(struct field* field, int x, int y);
void do_kill(char** board, struct field* field);
void do_kill_q(char** board, struct queen* field);
void show_moves(struct field* field);
struct queen* can_here_beat_q(struct queen* field, int x, int y);
struct q_killed* copy_q_kill(struct q_killed* k1, struct q_killed* k2);
struct queen* queen_single_beat(char** board, int x1, int y1, int x2, int y2, char my_pawn, char opp_pawn, struct queen* prev);
void queen_beat_possibilities(char** board, char my_pawn, char opp_pawn, struct queen* queen, int x, int y);
void q_moves(char** board, char my_pawn, char opp_pawn, struct q_move* queen, int x, int y);
bool can_q_here_move(struct q_move* pole, int x, int y);
void become_queen(char** board, char pawn, int x, int y);
void show_posibilities3(struct queen* pole);
bool is_correct(char** board, char my_pawn, char opp_pawn, int x1, int y1, int x2, int y2, struct field beat[][8], struct field mv[][8], struct queen q_tab[][8], struct q_move q_mv[][8]);
void swap_chars(char* a, char* b);
void show_q_moves(struct q_move* field);
void instruction();
void game();


#endif // HEADER_H_INCLUDED
