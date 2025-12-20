#ifndef RULES_H
#define RULES_H
#include"pieces.h"
#include"utility.h"
#include"undo.h"
int endgamecheck(int*kingpos,char**board);
int movevalidator(int x1,int y1,int x2,int y2,char**board,int*kingpos);
void moving(move *m, char **board, char *dead);
char check_promotion(char piece, int y2);
#endif