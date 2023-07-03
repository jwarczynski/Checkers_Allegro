#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstdlib>
#include "warcaby.h"
#include "header.h"

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
//void queen_beat_possibilities(char** board, char my_pawn, char opp_pawn, struct queen* queen, int x, int y);
//struct field* check_beat_possibilities(char** board, struct field* dest, int x, int y, char pawn);
void delete_board(char** board) {
    for (int i = 0; i < 8; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void copy_board(char** board, char** copied){

    for(int i =0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            copied[i][j] = board[i][j];
        }
    }
}
void catapult(char** board, int x, int y){

    board[x][y] = ' ';
}
void move_pawn(char** board, char pawn, int x1, int y1, int x2, int y2){

    board[x1][y1] = ' ';
    board[x2][y2] = pawn;
}
void zeruj_field(struct field* field){

    field->x = -1;
    field->y = -1;
    field->killed_pawns = NULL;
    for(int i=0;i<4;i++)
    {
        field->next[i] = NULL;
    }
}
bool read_coordinates(int* x1, int* y1, int* x2, int* y2){

    char v1[20];
    char c1[20];
    char v2[20];
    char c2[20];

    scanf(" %s%s%s%s", &c1, &v1, &c2, &v2);

    *x1 = atoi(v1);
    *y1 = atoi(c1);
    *x2 = atoi(v2);
    *y2 = atoi(c2);

    if(*x1 <= 0 || *x2 <= 0 || *y1 <= 0 || *y2 <= 0) return false;
    if(*x1 > 8 || *x2 > 8 || *y1 > 8 || *y2 > 8) return false;

    *x1 -= 1;
    *y1 -= 1;
    *x2 -= 1;
    *y2 -= 1;
    //printf("x1 = %d y1 = %d x2= %d, y2 = %d\n", *x1, *y1, *x2, *y2);

    return true;
}
void show_board(char** board){

   printf("   ----------------\n");
   for(int i=7;i>=0;i--)
   {
       printf("%d |", i+1);
       for(int j = 0;j<8;j++)
       {
           printf("%c ", board[i][j]);
       }
       printf("|\n");
   }
   printf("   ----------------\n   1 2 3 4 5 6 7 8 \n\n");
}
void read_board(char** board, char* name){

    FILE *f = fopen(name, "rt");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = fgetc(f);
            //printf("%c", board[i][j]);
        }
        fgetc(f);
    }
    fclose(f);
}
bool is_free(char** board, int x, int y){

    if(x<0 || x>7 || y<0 || y>7) return false;
    if(board[x][y] == ' ') return true;

    return false;
}
bool is_opponent(char** board, int x, int y, char pawn){
    //podajê w³asny pionek , a nie przeciwnika jako parametr
    //printf("%c", pawn);
    if(board[x][y] == pawn) return false;
    if(board[x][y] == toupper(pawn)) return false;
    if(board[x][y] == ' ') return false;
    if(board[x][y] == '-') return false;

    return true;
    // zwraca true jesli wspólrzędne określają pionka przeciwnika
}
bool is_on_board(int x, int y){

    if(x<0 || x>7 || y<0 || y>7) return false;

    return true;
}
void clean(struct field tab[][8], struct field mov[][8], struct queen qt[][8], struct q_move qm[][8]){

    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            tab[i][j].x = -1;
            tab[i][j].y = -1;
            tab[i][j].length = 0;
            tab[i][j].killed_pawns = NULL;
            mov[i][j].x = -1;
            mov[i][j].y = -1;
            mov[i][j].length = 0;
            mov[i][j].killed_pawns = NULL;
            qt[i][j].x = -1;
            qt[i][j].y = -1;
            qt[i][j].killed_by_q = NULL;
            qm[i][j].x = -1;
            qm[i][j].y = -1;
            for(int k = 0;k<4;k++)
            {
                tab[i][j].next[k] = NULL;
                mov[i][j].next[k] = NULL;
            }
            for(int k = 0;k<9;k++)
            {
                qt[i][j].next[k] = NULL;
            }
            for(int k =0;k<16;k++){
                qm[i][j].next[k] = NULL;
            }
        }
    }
}
bool is_possible_beat(char** board, int x, int y, int x_offset, int y_offset, char pawn){

    if(is_on_board(x+x_offset, y+y_offset) && is_free(board, x+x_offset, y+y_offset) && is_opponent(board, x+x_offset/2, y+y_offset/2, pawn)){
        return true;
    }
    return false;
}
struct killed* copy_kill(struct killed* k1, struct killed* k2){

    if(!k1){
        k2 = NULL;
        return k2;
    }
    else{

        struct killed* tmp = new struct killed;
        struct killed* first_k1 = new struct killed;
        first_k1 = k1;

        struct killed* created = new struct killed;
        k2 = created;
        k2->x = first_k1->x;
        k2->y = first_k1->y;
        k2->next = NULL;

        first_k1 = first_k1->next;

        while(first_k1){
            struct killed* new_field = new struct killed;
            new_field->x = first_k1->x;
            new_field->y = first_k1->y;
            new_field->next = NULL;
            tmp = k2;

            while(tmp->next){
                tmp = tmp->next;
            }
            tmp->next = new_field;
            first_k1 = first_k1->next;
        }
        delete first_k1;
        return k2;

    }
}
struct field* add_to_tree(char** board, char pawn, struct field* dest, int x, int y, int x_offset, int y_offset, struct killed* prev){

    dest->x = x+x_offset;
    dest->y = y+y_offset;
    dest->length += 1;

    struct killed* killed = new struct killed;
    killed->x = x+x_offset/2;
    killed->y = y+y_offset/2;
    killed->next = NULL;

    dest->killed_pawns = copy_kill(prev, dest->killed_pawns);
    if(!dest->killed_pawns){
       dest->killed_pawns = killed;
    }
    else{
        struct killed* tmp = dest->killed_pawns;
        while(tmp->next){
            tmp = tmp->next;
        }
        tmp->next = killed;
    }
//x_pos = 0;
                    //y_pos = 0;
    catapult(board, x+x_offset/2, y+y_offset/2);//x_pos = 0;
                    //y_pos = 0;
    move_pawn(board, pawn, x, y, x+x_offset, y+y_offset);
    //show_board(board);//x_pos = 0;//x_pos = 0;
                    //y_pos = 0;
                    //y_pos = 0;

    check_beat_possibilities(board, dest, x+x_offset, y+y_offset, pawn);
    return nullptr;
}
struct field* check_beat_possibilities_util(char** board, int x, int y, int of1, int of2, char pawn, struct field* dest, struct field* tmp, int id){

    if(is_possible_beat(board, x, y, of1, of2 ,pawn))
    {//x_pos = 0;
                    //y_pos = 0;
        //zeruj_field(tmp);
        //printf("%d %d\n", of1, of2);
        //printf("dest->kliled_pawns = %d\n", dest->killed_pawns);
        add_to_tree(board, pawn, tmp, x, y, of1, of2, dest->killed_pawns);
        return tmp;
        //dest->next[id] = tmp;
    }
    else
    {
        tmp = NULL;
        return tmp;
        //printf("%d\n", tmp);
    }
    printf("tmp[%d] = %d\n", id+1, tmp);
    return nullptr;
}
struct field* check_beat_possibilities(char** board, struct field* dest, int x, int y, char pawn){
    //własmy pionek

    char** tmp_board0 = new char*[8];
    char** tmp_board1 = new char*[8];
    char** tmp_board2 = new char*[8];
    char** tmp_board3 = new char*[8];
    for(int i = 0;i<8;i++)
    {
        tmp_board0[i] = new char[8];
        tmp_board1[i] = new char[8];
        tmp_board2[i] = new char[8];
        tmp_board3[i] = new char[8];
    }
    copy_board(board, tmp_board0);
    copy_board(board, tmp_board1);
    copy_board(board, tmp_board2);
    copy_board(board, tmp_board3);

    struct field* tmp1 = new struct field;
    struct field* tmp2 = new struct field;
    struct field* tmp3 = new struct field;
    struct field* tmp4 = new struct field;

    zeruj_field(tmp1);
    zeruj_field(tmp1);
    zeruj_field(tmp1);
    zeruj_field(tmp1);

    dest->next[0] = check_beat_possibilities_util(tmp_board0, x, y, 2, 2, pawn, dest, tmp1, 0);
    dest->next[1] = check_beat_possibilities_util(tmp_board1, x, y, 2, -2, pawn, dest, tmp2, 1);
    dest->next[2] = check_beat_possibilities_util(tmp_board2, x, y, -2, 2, pawn, dest, tmp3, 2);
    dest->next[3] = check_beat_possibilities_util(tmp_board3, x, y, -2, -2, pawn, dest, tmp4, 3);

    delete_board(tmp_board0);
    delete_board(tmp_board1);
    delete_board(tmp_board2);
    delete_board(tmp_board3);

    return nullptr;
}
void show_posibilities(struct field* field){

    int l = 0;
    for(int i = 0;i< 4;i++)
    {
        if(field->next[i])
        {
            show_posibilities(field->next[i]);
        }
        else l++;
    }
    if(l==4 && field->x >= 0){
        printf("x = %d, y = %d\n", field->x, field->y);
        struct killed* tmp = new struct killed;
        tmp = field->killed_pawns;
        printf("zbite pionki:\n");
        while(tmp){
            printf("x = %d, y = %d\n", tmp->x, tmp->y);
            tmp = tmp->next;
        }
    } //printf("x = %d, y = %d\nzbite: x = %d, y = %d\n", field->x, field->y, field->killed_pawns->x, field->killed_pawns->y);
}
struct field* check_move_possibilities(char** board, int x, int y, struct field* dest, char pawn){
    //podaj własny pionek

    struct field* tmp0 = new struct field;
    struct field* tmp1 = new struct field;
    zeruj_field(tmp0);
    zeruj_field(tmp1);
    if(pawn == 'a')
    {
        if(is_free(board, x+1, y+1)){
            tmp0->x = x+1;
            tmp0->y = y+1;
        }
        else tmp0 = NULL;
        if(is_free(board, x+1, y-1)){
            tmp1->x = x+1;
            tmp1->y = y-1;
        }
        else tmp1 = NULL;
    }
    if(pawn == 'b')
    {
        if(is_free(board, x-1, y+1)){
            tmp0->x = x-1;
            tmp0->y = y+1;
        }
        else tmp0 = NULL;
        if(is_free(board, x-1, y-1)){
            tmp1->x = x-1;
            tmp1->y = y-1;
        }
        else tmp1 = NULL;
    }
    dest->next[0] = tmp0;
    dest->next[1] = tmp1;

    return nullptr;
};
bool any_beat_util(struct field* field){

    int l = 0;
    for(int i = 0;i< 4;i++)
    {
        if(field->next[i])
        {
            if(any_beat_util(field->next[i])) return true;
        }
        else l++;
    }
    if(l==4 && field->x >= 0){
        return true;
    }
    return false;
}
bool any_beat(struct field tab[][8], char pawn, char** board){

    for(int i =0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j] == pawn){
                check_beat_possibilities(board, &tab[i][j], i, j, pawn);
                if(any_beat_util(&tab[i][j])) return true;
            }
        }
    }
    return false;
}
bool any_q_beat_util(struct queen* field){

    int l = 0;
    for(int i = 0;i< 9;i++)
    {
        if(field->next[i])
        {
            if(any_q_beat_util(field->next[i])) return true;
        }
        else l++;
    }
    if(l==9 && field->x >= 0){
        return true;
    }
    return false;
}
bool any_q_beat(struct queen tab[][8], char pawn, char opp_pawn, char** board){

    for(int i =0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j] == toupper(pawn)){
                queen_beat_possibilities(board, pawn, opp_pawn, &tab[i][j], i, j);
                if(any_q_beat_util(&tab[i][j])) return true;
            }
        }
    }
    return false;
}
bool can_here_move(struct field* field, int x, int y){

    if(field->next[0]){
        if(field->next[0]->x == x && field->next[0]->y == y) return true;
    }
    if(field->next[1]){
        if(field->next[1]->x == x && field->next[1]->y == y) return true;
    }
    return false;
}
bool is_end_of_game(char** board, char opp_pawn){

    //show_board(board);
    //printf("bylem tu opp_pawn = %c\n", opp_pawn);
    for(int i= 0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j] == opp_pawn || board[i][j] == toupper(opp_pawn)) return false;
        }
    }
    return true;
}
struct field* can_here_beat(struct field* field, int x, int y){

    int l = 0;
    for(int i = 0;i< 4;i++)
    {
        if(field->next[i])
        {
            struct field*tmp = can_here_beat(field->next[i], x, y);
            if(tmp) return tmp;
            //return can_here_beat(field->next[i], x, y);
            //if(can_here_beat(field->next[i], x, y)); //return true;
        }
        else l++;
    }
    //printf("l = %d x = %d  y = %d\n", l, x, y);
    if(l==4 && field->x >= 0){
        //printf("field->x = %d, field->y = %d\n", field->x, field->y);
        if(field->x == x && field->y == y) return field;
    }
    return nullptr;
}
void do_kill(char** board, struct field* field){

    struct killed* tmp = field->killed_pawns;
    while(tmp){
        board[tmp->x][tmp->y] = ' ';
        tmp = tmp->next;
    }
}
void do_kill_q(char** board, struct queen* field){

    struct q_killed* tmp = field->killed_by_q;
    while(tmp){
        board[tmp->x][tmp->y] = ' ';
        tmp = tmp->next;
    }
}
void show_moves(struct field* field){

    if(field->next[0]){
        printf("%d %d\n", field->next[0]->x, field->next[0]->y);
    }
    if(field->next[1]){
        printf("%d %d", field->next[1]->x, field->next[1]->y);
    }
}
struct queen* can_here_beat_q(struct queen* field, int x, int y){

    int l = 0;
    for(int i = 0;i< 9;i++)
    {
        if(field->next[i])
        {
            struct queen* tmp = can_here_beat_q(field->next[i], x, y);
            if(tmp) return tmp;
            //return can_here_beat(field->next[i], x, y);
            //if(can_here_beat(field->next[i], x, y)); //return true;
        }
        else l++;
    }
    //printf("l = %d x = %d  y = %d\n", l, x, y);
    if(l==9 && field->x >= 0){
        //printf("field->x = %d, field->y = %d\n", field->x, field->y);
        if(field->x == x && field->y == y) return field;
    }
    return nullptr;
}
struct q_killed* copy_q_kill(struct q_killed* k1, struct q_killed* k2){

    if(!k1){
        k2 = NULL;
        return k2;
    }
    else{

        struct q_killed* tmp = new struct q_killed;
        struct q_killed* first_k1 = new struct q_killed;
        first_k1 = k1;

        struct q_killed* created = new struct q_killed;
        k2 = created;
        k2->x = first_k1->x;
        k2->y = first_k1->y;
        k2->next = NULL;

        first_k1 = first_k1->next;

        while(first_k1){
            struct q_killed* new_field = new struct q_killed;
            new_field->x = first_k1->x;
            new_field->y = first_k1->y;
            new_field->next = NULL;
            tmp = k2;

            while(tmp->next){
                tmp = tmp->next;
            }
            tmp->next = new_field;
            first_k1 = first_k1->next;
        }
        delete first_k1;
        return k2;

    }
}
struct queen* queen_single_beat(char** board, int x1, int y1, int x2, int y2, char my_pawn, char opp_pawn, struct queen* prev){

    int x_zbity, y_zbity;
    if(x2 > x1 && y2 > y1){
        for(int i = 1; i<x2-x1;i++){
            if(board[x1+i][y1+i] == my_pawn || board[x1+i][y1+i] == toupper(my_pawn)) return NULL;
            if(board[x1+i][y1+i] == opp_pawn || board[x1+i][y1+i] == toupper(opp_pawn)){
                x_zbity = x1+i;
                y_zbity = y1+i;
                for(int j = 1;j<x2-x_zbity;j++){
                    if(board[x_zbity+j][y_zbity+j] != ' ') return NULL;
                }
                struct queen* q_field = new struct queen;
                q_field->x = x2;
                q_field->y = y2;
                struct q_killed* zbity = new struct q_killed;
                zbity->x = x_zbity;
                zbity->y = y_zbity;
                zbity->next = NULL;
                q_field->killed_by_q = copy_q_kill(prev->killed_by_q, q_field->killed_by_q);
                if(!q_field->killed_by_q){
                   q_field->killed_by_q = zbity;
                }
                else{
                    struct q_killed* tmp = q_field->killed_by_q;
                    while(tmp->next){
                        tmp = tmp->next;
                    }
                    tmp->next = zbity;
                }


                //q_field->killed_by_q = zbity;
                //update board
                catapult(board, x_zbity, y_zbity);
                move_pawn(board, my_pawn, x1, y1, x2, y2);
                //show_board(board);
                queen_beat_possibilities(board, my_pawn, opp_pawn, q_field, x2, y2);
                return q_field;
            }
        }
    }
    else if(x2 > x1 && y2 < y1){
        for(int i = 1; i<x2-x1;i++){
            if(board[x1+i][y1-i] == my_pawn || board[x1+i][y1-i] == toupper(my_pawn)) return NULL;
            if(board[x1+i][y1-i] == opp_pawn || board[x1+i][y1-i] == toupper(opp_pawn)){
                x_zbity = x1+i;
                y_zbity = y1-i;
                for(int j = 1;j<x2-x_zbity;j++){
                    if(board[x_zbity+j][y_zbity-j] != ' ') return NULL;
                }
                struct queen* q_field = new struct queen;
                q_field->x = x2;
                q_field->y = y2;
                struct q_killed* zbity = new struct q_killed;
                zbity->x = x_zbity;
                zbity->y = y_zbity;
                zbity->next = NULL;
                q_field->killed_by_q = copy_q_kill(prev->killed_by_q, q_field->killed_by_q);
                if(!q_field->killed_by_q){
                   q_field->killed_by_q = zbity;
                }
                else{
                    struct q_killed* tmp = q_field->killed_by_q;
                    while(tmp->next){
                        tmp = tmp->next;
                    }
                    tmp->next = zbity;
                }
                catapult(board, x_zbity, y_zbity);
                move_pawn(board, my_pawn, x1, y1, x2, y2);
                //show_board(board);
                queen_beat_possibilities(board, my_pawn, opp_pawn, q_field, x2, y2);
                return q_field;
            }
        }
    }
    else if(x2 < x1 && y2 < y1){
        for(int i = 1; i<x1-x2;i++){
            if(board[x1-i][y1-i] == my_pawn || board[x1-i][y1-i] == toupper(my_pawn)) return NULL;
            if(board[x1-i][y1-i] == opp_pawn || board[x1-i][y1-i] == toupper(opp_pawn)){
                x_zbity = x1-i;
                y_zbity = y1-i;
                for(int j = 1;j<x2-x_zbity;j++){
                    if(board[x_zbity-j][y_zbity-j] != ' ') return NULL;
                }
                struct queen* q_field = new struct queen;
                q_field->x = x2;
                q_field->y = y2;
                struct q_killed* zbity = new struct q_killed;
                zbity->x = x_zbity;
                zbity->y = y_zbity;
                zbity->next = NULL;
                q_field->killed_by_q = copy_q_kill(prev->killed_by_q, q_field->killed_by_q);
                if(!q_field->killed_by_q){
                   q_field->killed_by_q = zbity;
                }
                else{
                    struct q_killed* tmp = q_field->killed_by_q;
                    while(tmp->next){
                        tmp = tmp->next;
                    }
                    tmp->next = zbity;
                }
                catapult(board, x_zbity, y_zbity);
                move_pawn(board, my_pawn, x1, y1, x2, y2);
                //show_board(board);
                queen_beat_possibilities(board, my_pawn, opp_pawn, q_field, x2, y2);
                return q_field;
            }
        }
    }
    else{
        for(int i = 1; i<x1-x2;i++){
            if(board[x1-i][y1+i] == my_pawn || board[x1-i][y1+i] == toupper(my_pawn)) return NULL;
            if(board[x1-i][y1+i] == opp_pawn || board[x1-i][y1+i] == toupper(opp_pawn)){
                x_zbity = x1-i;
                y_zbity = y1+i;
                for(int j = 1;j<x2-x_zbity;j++){
                    if(board[x_zbity-j][y_zbity+j] != ' ') return NULL;
                }
                struct queen* q_field = new struct queen;
                q_field->x = x2;
                q_field->y = y2;
                struct q_killed* zbity = new struct q_killed;
                zbity->x = x_zbity;
                zbity->y = y_zbity;
                zbity->next = NULL;
                q_field->killed_by_q = copy_q_kill(prev->killed_by_q, q_field->killed_by_q);
                if(!q_field->killed_by_q){
                   q_field->killed_by_q = zbity;
                }
                else{
                    struct q_killed* tmp = q_field->killed_by_q;
                    while(tmp->next){
                        tmp = tmp->next;
                    }
                    tmp->next = zbity;
                }
                catapult(board, x_zbity, y_zbity);
                move_pawn(board, my_pawn, x1, y1, x2, y2);
                //show_board(board);
                queen_beat_possibilities(board, my_pawn, opp_pawn, q_field, x2, y2);
                return q_field;
            }
        }
    }
    return nullptr;
}
void queen_beat_possibilities(char** board, char my_pawn, char opp_pawn, struct queen* queen, int x, int y){

    // kopiowanie planszy w ifie
    int k = 0;
    for(int j = 0;j<9;j++){
        queen->next[j]= NULL;
    }
    //struct queen** q_tab = new struct queen*[9];
    //printf("%d", q_tab[0]);
    for(int i = 2; i <= 7;i++){
        if(is_on_board(x-i, y-i)){
            if(is_free(board, x-i, y-i)){
                char** tmp_board = new char*[8];
                for(int i = 0;i<8;i++)
                {
                    tmp_board[i] = new char[8];
                }
                copy_board(board, tmp_board);
                //printf("przed k = %d, x = %d, y = %d, x-i = %d, y-i = %d\n", k, x, y, x-i, y-i);
                queen->next[k++] = queen_single_beat(tmp_board, x, y, x-i, y-i, my_pawn, opp_pawn, queen);
                //printf("queen->next[%d++] = %d  x-i = %d  y-i = %d\n", k-1, queen->next[k-1], x-+i, y-i);
                delete_board(tmp_board);
            }
        }
        if(is_on_board(x-i, y+i)){
            if(is_free(board, x-i, y+i)){
                char** tmp_board = new char*[8];
                for(int i = 0;i<8;i++)
                {
                    tmp_board[i] = new char[8];
                }
                copy_board(board, tmp_board);
                //printf("przed k = %d, x = %d, y = %d, x-i = %d, y+i = %d\n", k, x, y, x-i, y+i);
                queen->next[k++] = queen_single_beat(tmp_board, x, y, x-i, y+i, my_pawn, opp_pawn, queen);
                //printf("queen->next[%d++] = %d  x-i = %d  y+i = %d\n", k-1, queen->next[k-1], x-i, y+i);
                delete_board(tmp_board);
            }
        }
        if(is_on_board(x+i, y-i)){
            if(is_free(board, x+i, y-i)){
                char** tmp_board = new char*[8];
                for(int i = 0;i<8;i++)
                {
                    tmp_board[i] = new char[8];
                }
                copy_board(board, tmp_board);
                //printf("przed k = %d, x = %d, y = %d, x+i = %d, y-i = %d\n", k, x, y, x+i, y-i);
                queen->next[k++] = queen_single_beat(tmp_board, x, y, x+i, y-i, my_pawn, opp_pawn, queen);
                //printf("queen->next[%d++] = %d  x+i = %d  y-i = %d\n", k-1, queen->next[k-1], x+i, y-i);
                delete_board(tmp_board);
            }
        }
        if(is_on_board(x+i, y+i)){
            if(is_free(board, x+i, y+i)){
                char** tmp_board = new char*[8];
                for(int i = 0;i<8;i++)
                {
                    tmp_board[i] = new char[8];
                }
                copy_board(board, tmp_board);
                //printf("przed k = %d, x = %d, y = %d, x+i = %d, y+i = %d\n", k, x, y, x+i, y+i);
                queen->next[k++] = queen_single_beat(tmp_board, x, y, x+i, y+i, my_pawn, opp_pawn, queen);
                //printf("queen->next[%d++] = %d  x+i = %d  y+i = %d\n", k-1, queen->next[k-1], x+i, y+i);
                delete_board(tmp_board);
            }
        }
    }
}
void q_moves(char** board, char my_pawn, char opp_pawn, struct q_move* queen, int x, int y){

    //printf("my_pawn = %c  opp_pawn = %c, x = %d, y = %d\n", my_pawn, opp_pawn, x, y);
    int k = 0;
    for(int j = 0;j<16;j++){
        queen->next[j]= NULL;
    }
    for(int i = 1;i<8;i++){
        if(is_on_board(x-i, y-i)){
            if(board[x-i][y-i] != ' ') break;
            else{
                struct q_move* nowy = new struct q_move;
                nowy->x = x-i;
                nowy->y = y-i;
                queen->next[k++] = nowy;
            }
        }
    }
    for(int i = 1;i<8;i++){
        if(is_on_board(x-i, y+i)){
            if(board[x-i][y+i] != ' ') break;
            else{
                struct q_move* nowy = new struct q_move;
                nowy->x = x-i;
                nowy->y = y+i;
                queen->next[k++] = nowy;
            }
        }
    }
    for(int i = 1;i<8;i++){
        if(is_on_board(x+i, y-i)){
            if(board[x+i][y-i] != ' ') break;
            else{
                struct q_move* nowy = new struct q_move;
                nowy->x = x+i;
                nowy->y = y-i;
                queen->next[k++] = nowy;
            }
        }
    }
    for(int i = 1;i<8;i++){
        if(is_on_board(x+i, y+i)){
            if(board[x+i][y+i] != ' ') break;
            else{
                struct q_move* nowy = new struct q_move;
                nowy->x = x+i;
                nowy->y = y+i;
                queen->next[k++] = nowy;
            }
        }
    }
}
bool can_q_here_move(struct q_move* pole, int x, int y){

    for(int i = 0;i<16;i++){
        if(pole->next[i]){
            if(pole->next[i]->x == x && pole->next[i]->y == y){
                return true;
            }
        }
    }
    return false;
}
void become_queen(char** board, char pawn, int x, int y){

    if(pawn == 'a' && x == 7){
        board[x][y] = toupper(pawn);
    }
    if(pawn == 'b' && x == 0){
        board[x][y] = toupper(pawn);
    }
}
void show_posibilities3(struct queen* pole){

    int l = 0;
    for(int i = 0;i< 9;i++)
    {
        //printf("pole->next[%d] = %d\n", i, pole->next[i]);
        if(pole->next[i])
        {
            //printf("jestem i = %d\n", i);
            show_posibilities3(pole->next[i]);
        }
        else l++;
    }
    if(l==9 && pole->x >= 0){
        printf("x = %d, y = %d\n", pole->x, pole->y);
        struct q_killed* tmp = new struct q_killed;
        tmp = pole->killed_by_q;
        printf("zbite pionki:\n");
        while(tmp){
            printf("x = %d, y = %d\n", tmp->x, tmp->y);
            //printf("chyba wiem\n");
            //printf("tmp->next = %d\n", tmp->next);
            tmp = tmp->next;
            //printf("jendak\n");
        }
    } //printf("x = %d, y = %d\nzbite: x = %d, y = %d\n", field->x, field->y, field->killed_pawns->x, field->killed_pawns->y);
}
bool is_correct(char** board, char my_pawn, char opp_pawn, int x1, int y1, int x2, int y2, struct field beat[][8], struct field mv[][8], struct queen q_tab[][8], struct q_move q_mv[][8]){

    if(!is_on_board(x1, y1)) return false;
    if(board[x1][y1] != my_pawn && board[x1][y1] != toupper(my_pawn)) return false;
    if(!is_on_board(x2, y2)) return false;
    if(board[x1][y1] == toupper(my_pawn)){
        queen_beat_possibilities(board, my_pawn, opp_pawn, &q_tab[x1][y1], x1, y1);
        struct queen* tmpq = can_here_beat_q(&q_tab[x1][y1], x2, y2);
        if(tmpq){
            do_kill_q(board, tmpq);
            move_pawn(board, toupper(my_pawn), x1, y1, x2, y2);
            return true;
        }
        else{
            if(any_q_beat(q_tab, my_pawn, opp_pawn, board)) return false;
        }
    }
    if(any_q_beat(q_tab, my_pawn, opp_pawn, board)) return false;
    check_beat_possibilities(board, &beat[x1][y1], x1, y1, my_pawn);
    struct field* tmp = can_here_beat(&beat[x1][y1], x2, y2);
    if(tmp){
        do_kill(board, tmp);
        move_pawn(board, my_pawn, x1, y1, x2, y2);
        become_queen(board, my_pawn, x2, y2);
        return true;
    }
    else{
        if(any_beat(beat, my_pawn, board)) return false;
        //printf("dotarłem az tu\n");
    }
    if(board[x1][y1] == toupper(my_pawn)){
        q_moves(board, my_pawn, opp_pawn, &q_mv[x1][y1], x1, y1);
        if(can_q_here_move(&q_mv[x1][y1], x2, y2)){
            move_pawn(board, toupper(my_pawn), x1, y1, x2, y2);
            return true;
        }
        return false;
    }
    check_move_possibilities(board, x1, y1, &mv[x1][y1], my_pawn);
    if(can_here_move(&mv[x1][y1], x2, y2)){
        move_pawn(board, my_pawn, x1, y1, x2, y2);
        become_queen(board, my_pawn, x2, y2);
        return true;
    }
    return false;
}
void swap_chars(char* a, char* b){

    char tmp = *b;
    *b = *a;
    *a = tmp;
}
void show_q_moves(struct q_move* field){

    for(int i = 0;i<16;i++){
        if(field->next[i]) printf("%d %d\n", field->next[i]->x, field->next[i]->y);
    }
}
void instruction(){

    printf("aby wykonac ruch nalezy najpiew podac wspolrzedne wlasnego\n"
           "pionka, a nastepnie wporzedne pola na ktore chcemy sie przemiescic\n"
           "wporzedne nalezy podawac po spacji zaczynajac od osi X np.:\n"
           "wpisanie: 5 5 4 4, spowoduje przmieszczeni pionka z pozycji 5 5\n"
           "na pozycje 4 4. Ruch nalezy potwierdzic enterem.\n\n");

    printf("Jesli jest mozliwosc bicia to nie wolno wykonac innego ruchu niz bicie.\n"
           "Dodatkowo jesli jest mozliwe bicie zarowno pionkiem, jak i damka, to nie wolno wykonac bicia pionem.\n"
           "Jesli po wykonaniu bicia jest dalse mozliwe bicie, to trzeba je wykonac, przy czym,\n"
           "jesli sa mozliwe bicia w roznych kierunkach, wybor co do bicia nalezy do gracza\n\n");
}
//void game(){
//
//    int x1, x2, y1, y2;
//    char PAWN1 = 'a', PAWN2 = 'b';
//    char name[] = "test_board.txt";
//    char* board[8];
//    struct field tab[8][8];
//    struct field tab_m[8][8];
//    struct queen q_tab[8][8];
//    struct q_move q_m[8][8];
//    for (int i = 0; i < 8; i++)
//    {
//        board[i] = new char[8];
//    }
//    read_board(board, name);
//    show_board(board);
//    clean(tab, tab_m, q_tab, q_m);
//    do{
//        do{
//            read_coordinates(&x1, &y1, &x2, &y2);
//        }while(!is_correct(board, PAWN1, PAWN2, x1, y1, x2, y2, tab, tab_m, q_tab, q_m));
//        system("cls");
//        show_board(board);
//        clean(tab, tab_m, q_tab, q_m);
//        swap_chars(&PAWN1, &PAWN2);
//    }while(!is_end_of_game(board, PAWN1));
//    printf("    END OF GAME\n\n");
//}
//
//
//int main(){
//
//    char choice;
//    printf("i - pokaz instrukcje\nn - nowa gra\ne - wyjscie\n");
//    do{
//        scanf("%c", &choice);
//        printf("\n");
//        if(choice == 'i') instruction();
//        if(choice == 'n') game();
//    }while(choice != 'e');
//}

