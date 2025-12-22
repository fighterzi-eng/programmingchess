#ifndef UNDO_H
#define UNDO_H
typedef struct {
    int x1, y1, x2, y2;
    char p1, p2, promotion;
    int wkx_before, wky_before, bkx_before, bky_before;  //  king pos saves
    // NEW:
    int rook_x1, rook_x2;
    char r_p1;
    char ep_captured_p;
} move;

extern move moves[1024];
void undo(char **board,move move,int *whitekingpos, int* blackkingpos,char*dead);
void redo(char**board,move move,int whitekingpos[2], int blackkingpos[2],char*dead);
void addmove(int x1,int y1,char p1,int x2,int y2,char p2,int n,char promotion);
//void rumode(char **board,int *n);





#endif