#ifndef PIECES_H
#define PIECES_H
#include"utility.h"
//char promote();
int pawn(int x1,int y1,int x2,int y2,char**board);
//int pawnwthpromote(int x1,int y1,int x2,int y2,char**board);
int rook(int x1, int y1, int x2, int y2, char **board);
int knight(int x1,int y1,int x2,int y2,char**board);
int bishop(int x1, int y1, int x2, int y2, char **board);
int queen(int x1,int y1,int x2,int y2,char**board);
int king(int x1, int y1, int x2, int y2, char **board);

#endif