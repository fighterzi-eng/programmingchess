#ifndef UNDO_H
#define UNDO_H
typedef struct {
    int x1, y1;
    char p1;       // moving piece before move
    int x2, y2;
    char p2;       // captured piece (or EMPTY)
    char promotion; // if a pawn promotes, store new piece here; else 0

    int wkx_before, wky_before;
    int bkx_before, bky_before;
} move;


extern move moves[1024];
void undo(char **board,move move,int whitekingpos[2], int blackkingpos[2]);
void redo(char**board,move move,int whitekingpos[2], int blackkingpos[2]);
void addmove(int x1,int y1,char p1,int x2,int y2,char p2,int n);
//void rumode(char **board,int *n);





#endif