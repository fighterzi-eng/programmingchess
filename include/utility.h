#ifndef UTILITY_H
#define UTILITY_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EMPTY(c) ((c) == '.' || (c) == '-')   // just a suggestion not yet implemented but using #define could save us space
#define WHITE(c) islower(c)
#define BLACK(c) isupper(c)
extern int ep_target_x;
extern int ep_target_y;
 // Global variables for en passant target square

extern bool wk_castle_ks;
extern bool wk_castle_qs;
extern bool bk_castle_ks;
extern bool bk_castle_qs;//castle rights

char** boardmaker(int *whitekingpos, int *blackkingpos);
int inside(int x, int y);
int inCheck(int kx, int ky, char **board);
void boardprintWH(char**board);
void boardprintBL(char**board);
int parseMove(char *move, int *x1, int *y1, int *x2, int *y2);
void updateKingPositions(char **board, int *whitekingpos, int *blackkingpos);//updating king positions after loading
//int checkdanger(int x,int y,char**board);
#endif