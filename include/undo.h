#ifndef UNDO_H
#define UNDO_H
typedef struct {
    int x1, y1;
    char p1;
    int x2, y2;
    char p2;
} move;

extern move moves[1024];
void undo(char **board,move move);
void redo(char**board,move move);
void addmove(int x1,int y1,char p1,int x2,int y2,char p2,int n);
void rumode(char **board,int *n);





#endif