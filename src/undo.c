#include"include/undo.h"
#include"include/utility.h"
typedef struct 
{
    int x1;
    int y1;
    char p1;
    int x2;
    int y2;
    char p2;

    
}move;

move moves[1024];
void undo(char **board,move move){
    board[move.y2][move.x2]=move.p1;
    board[move.y1][move.x1]=move.p2;

}
void redo(char**board,move move){
    board[move.y2][move.x2]=move.p2;
    board[move.y1][move.x1]=move.p1;
}

void addmove(int x1,int y1,char p1,int x2,int y2,char p2,int n){
    moves[n].p1=p1;
    moves[n].p2=p2;
    moves[n].x1=x1;
    moves[n].x2=x2;
    moves[n].y1=y1;
    moves[n].y2=y2;

}
//n is the same as the number of turns and its taken by reference to avoid logical errors when redoing again
void rumode(char **board,int *n){
    int start=*n;
    char op='/';
    while(op!='e'){
        scanf("%c",&op);
        switch (op)
        {
        case 'u' :
            if (*n==0) continue;
            undo(board,moves[*n]);
            *n--;
            break;
        case 'r' :
             if (*n==start) continue;
            redo(board,moves[*n+1]);
            *n++;
            break;
        
        default:
            printf("invalid input");
            continue;
            break;
        }
        boardprint(board);

    }
    //no need to clear the array bec it will do this by its own bec the n of the turns is decreased

}
