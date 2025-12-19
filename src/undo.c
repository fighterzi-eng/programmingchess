#include"include/undo.h"
#include"include/utility.h"
/*typedef struct 
{
    int x1;
    int y1;
    char p1;
    int x2;
    int y2;
    char p2;

    
}move;*/ //we already have this in the header file cant define it twice

move moves[1024];
void undo(char **board, move m, int whitekingpos[2], int blackkingpos[2])
{
    board[m.y1][m.x1] = m.p1;
    board[m.y2][m.x2] = m.p2;

    whitekingpos[0] = m.wkx_before;
    whitekingpos[1] = m.wky_before;
    blackkingpos[0] = m.bkx_before;
    blackkingpos[1] = m.bky_before;
}

void redo(char **board, move m, int whitekingpos[2], int blackkingpos[2])
{
    board[m.y2][m.x2] = m.p1;
    board[m.y1][m.x1] = (m.p2 == '.' || m.p2 == '-') ? m.p2 : '.';

    if (m.p1 == 'k') {
        whitekingpos[0] = m.x2;
        whitekingpos[1] = m.y2;
    }
    if (m.p1 == 'K') {
        blackkingpos[0] = m.x2;
        blackkingpos[1] = m.y2;
    }
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
/*void rumode(char **board,int *n){
    int start=*n;
    char op='/';
    while(op!='e'){ //i think we should not read input in here input should be handled in main
        scanf(" %c",&op);//space before %c to ignore whitespace characters
        switch (op)
        {
        case 'u' :
            if (*n==0) continue;
            undo(board,moves[*n-1]);//index was off by one i fixed it
            *n--;
            break;
        case 'r' :
             if (*n==start) continue;
            redo(board,moves[*n]);  //you seemed to forget that arrays start from 0 moves[0] is the first move so i fixed it
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
*/