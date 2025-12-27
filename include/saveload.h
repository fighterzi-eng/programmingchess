#ifndef SAVELOAD_H
#define SAVELOAD_H
#include"include/utility.h"
#include "include/undo.h"
#include "include/utility.h"
#include "include/rules.h"
//#include "undo.h"

// Save and load functions
//void save_game(const char *filename, move *moves, int n);
//int load_game(const char *filename, char **board, move *moves, int *n,int *whiteKingPos, int *blackKingPos);
//void boardreset(char **board);
//void save_gametxt( char *filename, char**board);
//void load(char*filename,char**board);
//void save_game(char *filename, move *moves, int n);
//int load_game(char *filename,char **board,move *moves,int *n,int *whiteKingPos,int *blackKingPos,char*dead);
void save_game_bin(int* n, char *dead,move*moves);
int load_game_bin(char **board, int *n, int *whitekingpos, int *blackkingpos, char *dead,int* ep_target_x,int* ep_target_y,
bool *wk_castle_ks, bool* wk_castle_qs,
bool* bk_castle_ks , bool* bk_castle_qs,move*moves );
#endif
