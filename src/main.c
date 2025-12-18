#include"include/utility.h"
#include"include/rules.h"
#include"include/pieces.h"
#include"include/undo.h"
//at the current time the program will not work because boaard maker makes an empty board
int main(){
    int n=0;
    char dead[32];
    // here we should have an option to load a game or start a new game
    //we should add the pieces to the board maker
    char**board=boardmaker();
    //we should put the start postion here as an intitial valuue
    int blackkingpos[2];
    int whitekingpos[2];
    boardprint(board);
    //both are in x,y
    int w=0,b=0;
    while(w==0&&b==0){
        //we also shoud add here at the start of the loop an option to save and continue normally after saving
        //for now and for easier testing
        //the redo mode will be bound to x1=10
        //and saving to x1=11
        int x1,x2,y1,y2;
        scanf("%d",&x1);
        if(x1==10){
         printf("r for redo ,u for undo and e for exit");
         rumode(board,&n);
         continue;}
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        //if  (x1==11){ save(board); continue;}
        
        if (!inside(x1,y1)||!inside(x2,y2)){ continue;
            printf("out of bounds");}
        //0 is whte black is 1
        if(n%2==0){
            if (isupper(board[y1][x1])!=0){ continue;
                printf("invalid piece");}
            if(movevalidator(x1,y1,x2,y2,board,whitekingpos)!=0){
                printf("invalid move try again");
                continue;
            }
            addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n);
            if (board[y1][x1]=='p') pawnwthpromote(x1,y1,x2,y2,board);
            else if(board[y1][x1]=='k'){
                moving(x1,y1,x2,y2,board,dead);
                whitekingpos[0]=x2;
                whitekingpos[1]=y2;

            }
            else moving(x1,y1,x2,y2,board,dead);
            n++;
            

        }
        else if(n%2==1){
            if (isupper(board[y1][x1])==0){ continue;
                printf("invalid piece");}
            if(movevalidator(x1,y1,x2,y2,board,blackkingpos)!=0){
                printf("invalid move try again");
                continue;
            }
            addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n);
            if (board[y1][x1]=='P') pawnwthpromote(x1,y1,x2,y2,board);
            else if(board[y1][x1]=='K'){
                moving(x1,y1,x2,y2,board,dead);
                blackkingpos[0]=x2;
                blackkingpos[1]=y2;

            }
            else moving(x1,y1,x2,y2,board,dead);
            n++;

        }
        boardprint(board);
        w=endgamecheck(whitekingpos,board);
        b=endgamecheck(blackkingpos,board);

    }
    if(w==2||b==2) printf("game over the result is a draw");
    else if(w==1) printf("game over the result is black wins");
    else if(b==1) printf("game over the result is white wins");
    //this  is probably wron because we assigned it in a function so its not tracked ,i placed it here to remind us to do it later
    free(board);





    return 0;
}