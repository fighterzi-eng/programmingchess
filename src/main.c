#include"include/rules.h"
#include"include/utility.h"
#include"include/pieces.h"
#include"include/undo.h"
#include"include/saveload.h"
int ep_target_x, ep_target_y;
bool wk_castle_ks = true, wk_castle_qs = true;
bool bk_castle_ks = true, bk_castle_qs = true;//castle rights

int main() {
    int n = 0;
    char dead[32];
    memset(dead, 0, sizeof(dead));
    char menu[8];        // <-- NEW: menu input buffer
    char input[32];      // <-- move input buffer
    int x1, y1, x2, y2;
    char op;
    int blackkingpos[2];
    int whitekingpos[2];
    char **board = boardmaker(whitekingpos, blackkingpos);
    /* -------- Menu input -------- */
    printf("enter l to load game or anything else to start a new game\n");
    if (!fgets(menu, sizeof(menu), stdin)) {
        printf("input error\n");
        return 1;
    }

    op = menu[0];

    if (op == 'l') {
        int x=load_game("save.bin", board,moves,&n,whitekingpos,blackkingpos,dead);
        deadn = 0; 
        memset(dead, 0, sizeof(dead));
    }

    /* -------- Game initialization -------- */
    ep_target_x = 0;
    ep_target_y = 0;

    updateKingPositions(board, whitekingpos, blackkingpos);
    boardprintWH(board);

    memset(moves, 0, sizeof(moves));

    int w = 0, b = 0;
      printf("\nenter your move in format ex: (e2e4):\n");
      printf("enter 'undo' to undo last move or 'redo' to redo last undone move you can also write'save' to save\n");

    /* -------- Main game loop -------- */
    while (w == 0 && b == 0) {
        if(inCheck(blackkingpos[0],blackkingpos[1],board)==1) printf("black is checked");
        if(inCheck(whitekingpos[0],whitekingpos[1],board)==1) printf("black is checked");

      
    if (n % 2 == 0) {
      printf("White to move\n");
     } else {
      printf("Black to move\n");
     }
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        /* Strip newline */
        input[strcspn(input, "\n")] = '\0';

        if (n!=0){
            moves[n].wkx_before = whitekingpos[0]; //saving king positions before the move
            moves[n].wky_before = whitekingpos[1];
            moves[n].bkx_before = blackkingpos[0];
            moves[n].bky_before = blackkingpos[1];
        }
    
        if (strcmp(input, "save") == 0) {
            save_game("save.bin", moves,n);
            continue;
        }

        if (strcmp(input, "exit") == 0) break;

        //we need to think a bit about how the undo redo bec if we excedded the original n we will get unexpected results
        if (strcmp(input, "undo") == 0) {
             //added undo redo functionality Here directly
             if (n==0) continue;
            undo(board, moves[n - 1], whitekingpos, blackkingpos, dead);
            n--;
            if(n%2==0)
            boardprintWH(board);
            else boardprintBL(board);
            continue;
        }
        if (strcmp(input, "redo") == 0) {
            redo(board, moves[n], whitekingpos, blackkingpos, dead);
            n++;
            if(n%2==0)
            boardprintWH(board);
            else boardprintBL(board);
            continue;
        }
        if (parseMove(input, &x1, &y1, &x2, &y2)) {
            printf("Bad move format\n");
        } else {
        }
                //0 is whte black is 1
                if(n%2==0){
                    if (isupper(board[y1][x1])!=0){ 
                        printf("invalid piece");
                         continue;}
                    if(movevalidator(x1,y1,x2,y2,board,whitekingpos)!=0){
                        printf("invalid move try again");
                        continue;
                    }
                    char prom=check_promotion(board[y1][x1],y2);
                    addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n,prom);
                    if(board[y1][x1]=='k'){
                        moving(&moves[n],board,dead);
                        whitekingpos[0]=x2;
                        whitekingpos[1]=y2;

                    }
                    else moving(&moves[n],board,dead);
                    n++;
                    

                }
                else if(n%2==1){
                    if (isupper(board[y1][x1])==0){ printf("invalid piece");continue; //printf before continue
                        }
                    if(movevalidator(x1,y1,x2,y2,board,blackkingpos)!=0){
                        printf("invalid move try again");
                        continue;
                    }
                    char prom=check_promotion(board[y1][x1],y2);
                    addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n,prom);
                    if(board[y1][x1]=='K'){
                        moving(&moves[n],board,dead);
                        blackkingpos[0]=x2;
                        blackkingpos[1]=y2;

                    }
                    else moving(&moves[n],board,dead);
                    n++;

                }
            if(n%2==0)
            boardprintWH(board);
            else boardprintBL(board);
                print_dead(dead);  
                w=endgamecheck(whitekingpos,board);
                b=endgamecheck(blackkingpos,board);

    }
    if(w==2||b==2) printf("Stalemate The game is a draw");
    else if(w==1) printf("Checkmate black wins");
    else if(b==1) printf("Checkmate white wins");
    printf("\n");
   for (int i = 0; i < 10; i++)
    free(board[i]);
free(board);
printf("by john bassem and justin jimmy\n");
printf("thank you for playing\n");

    return 0;
}