#ifndef UNDO_H
#define UNDO_H

#include"utility.h"
#include "rules.h"
#include"move.h"

extern move moves[1024];
void printMoveHistoryRaw(move *moves, int total_moves);
void undo(char **board,move move,int *whitekingpos, int* blackkingpos,char*dead);
void redo(char**board,move move,int whitekingpos[2], int blackkingpos[2],char*dead);
void addmove(int x1,int y1,char p1,int x2,int y2,char p2,int n,char promotion, int *wk, int *bk);
//void rumode(char **board,int *n);





#endif