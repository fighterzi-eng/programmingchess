#ifndef RULES_H
#define RULES_H
#include"include/pieces.h"
#include"include/utility.h"
int endgamecheck(int*kingpos,char**board);
int movevalidator(int x1,int y1,int x2,int y2,char**board,int*kingpos);
void moving(int x1,int y1,int x2,int y2,char**board,char*dead);
#endif