#include"include/utility.h"
#include"include/rules.h"
#include"include/pieces.h"
#include"include/undo.h"
#include"include/saveload.h"
//at the current time the program will not work because boaard maker makes an empty board *FIXED*
int main(){
    int n=0;
    char dead[32];
    char input[32];
    int x1, y1, x2, y2;
    // here we should have an option to load a game or start a new game
    //we should add the pieces to the board maker
    char**board=boardmaker();
    //we should put the start postion here as an intitial valuue //already included in new boardmaker
    int blackkingpos[2];
    int whitekingpos[2];
    boardprint(board);
    //both are in x,y
    int w=0,b=0;
    while(w==0&&b==0){
        //*DONE*we also shoud add here at the start of the loop an option to save and continue normally after saving
        //for now and for easier testing
        //*Changed to undo and redo directly* (the redo mode will be bound to x1=10)
        //*DONE* WE need to convert X1,X2 from chess notation to array notation first (a-h)->(1-9)
//Added move parser in utility.c


printf("enter your move in format ex: (e2e4):");
printf("\nenter 'undo' to undo last move or 'redo' to redo last undone move\n");

fgets(input, sizeof(input), stdin); // Read user input
input[strcspn(input, "\n")] = '\0';
  
  
  moves[n].wkx_before = whitekingpos[0]; //saving king positions before the move
  moves[n].wky_before = whitekingpos[1];
  moves[n].bkx_before = blackkingpos[0];
  moves[n].bky_before = blackkingpos[1];
    
if (strcmp(input, "save") == 0) {
    save_game("game.chs", moves, n);
    continue;
}

if (strcmp(input, "load") == 0) {
    load_game("game.chs", board, moves, &n,
              whitekingpos, blackkingpos);
    boardprint(board);
    continue;
}


if (strcmp(input, "undo") == 0) { //added undo redo functionality Here directly
    undo(board, moves[n - 1], whitekingpos, blackkingpos);
    n--;
    boardprint(board);
    continue;
}
if (strcmp(input, "redo") == 0) {
    redo(board, moves[n], whitekingpos, blackkingpos);
    n++;
    boardprint(board);
    continue;
}
if (parseMove(input, &x1, &y1, &x2, &y2)) {
    printf("Bad move format\n");
} else {
    printf("From (%d,%d) to (%d,%d)\n", x1, y1, x2, y2);
}

        
       // if (!inside(x1,y1)||!inside(x2,y2)){ continue; //already handled in parseMove can remove
         //   printf("out of bounds");}
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
            if (isupper(board[y1][x1])==0){ printf("invalid piece");continue; //printf before continue
                }
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
   
  //correctly free the allocated memory 
   for (int i = 0; i < 10; i++)
    free(board[i]);
free(board);

    return 0;
}