#include"include/rules.h"
#include"include/utility.h"
#include"include/pieces.h"
#include"include/undo.h"
#include"include/saveload.h"
int ep_target_x, ep_target_y;
bool wk_castle_ks = true, wk_castle_qs = true;
bool bk_castle_ks = true, bk_castle_qs = true;//castle rights
bool use_fancy_graphics = true;
int max_history = 0;
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
    printf("Welcome to our Chess Game!\n");

    /* -------- Graphics Toggle -------- */
    printf("Enable ASCII graphics? (y/n): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] == 'n' || input[0] == 'N') {
        use_fancy_graphics = false;
    } else {
        use_fancy_graphics = true;
    }
printf("---------------Menu---------------\n");
printf("               Start               \n");
printf("               Load                \n");
printf("               Exit                \n");
printf("----------------------------------\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline
    if (strcmp(input, "exit") == 0||strcmp(input, "Exit") == 0) {
        printf("\nMade by: John Bassem and Justin Jimmy \n");
        printf("Thank you for playing!\n");
        return 0;
    }
    if (strcmp(input, "load") == 0||strcmp(input, "Load") == 0) {
       load_game_bin(board, &n, whitekingpos, blackkingpos, dead);

        if(n%2==0)
            boardprintWH(board);
            else boardprintBL(board);
            }

    /* -------- Game initialization -------- */
    ep_target_x = 0;
    ep_target_y = 0;

    updateKingPositions(board, whitekingpos, blackkingpos);
    boardprintWH(board);

    memset(moves, 0, sizeof(moves));

    int w = 0, b = 0;
      printf("\nEnter your move in format ex: (e2e4):\n");
      printf("Enter 'undo' to undo last move or 'redo' to redo last undone move you can also write'save' to save\n");


          /* -------- Main game loop -------- */
while (w == 0 && b == 0) {
    if(inCheck(blackkingpos[0], blackkingpos[1], board) == 1) printf("Black is in check! \n");
    if(inCheck(whitekingpos[0], whitekingpos[1], board) == 1) printf("White is in check! \n");

    if (n % 2 == 0) {
        printf("White to move\n");
        printf("Enter your move: ");}

    else {
        printf("Black to move\n");
        printf("Enter your move: ");
    }
    if (!fgets(input, sizeof(input), stdin)) break;
    input[strcspn(input, "\n")] = '\0';
    input[strcspn(input, "\n")] = 0; // Remove newline
    if (strcmp(input, "exit") == 0||strcmp(input, "Exit") == 0) {
        printf("\nMade by: John Bassem and Justin Jimmy \n");
        printf("Thank you for playing!\n");
        return 0;
    }
    // 1. CHECK COMMANDS FIRST before saving "before" positions
    if (strcmp(input, "save") == 0||strcmp(input, "Save") == 0) {
        save_game_bin(n, dead);
        while (getchar() != '\n'){

        }; // CLEAR THE SCANF BUFFER
        continue;
    } 
    else if (strcmp(input, "load") == 0||strcmp(input, "Load") == 0) {
        load_game_bin(board, &n, whitekingpos, blackkingpos, dead);
        while (getchar() != '\n'){

        }; // CLEAR THE SCANF BUFFER
        if(n % 2 == 0) boardprintWH(board);
        else boardprintBL(board);
        continue;
    }
          //we need to think a bit about how the undo redo bec if we excedded the original n we will get unexpected results *unlickily to reach move 1024*
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
             if (n >= max_history) {
             printf("Nothing to redo!\n");
              continue;
             }
            redo(board, moves[n], whitekingpos, blackkingpos, dead);
            n++;
            if(n%2==0)
            boardprintWH(board);
            else boardprintBL(board);
            continue;
        }
       else if (parseMove(input, &x1, &y1, &x2, &y2)) {
            printf("Bad move format\n");
            continue;
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
                    addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n,prom,whitekingpos,blackkingpos);
                     n++; 
                     max_history = n;
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
                    addmove(x1,y1,board[y1][x1],x2,y2,board[y2][x2],n,prom,whitekingpos,blackkingpos);
                     n++; 
                     max_history = n;
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
printf("by John Bassem and Justin Jimmy\n");
printf("Thank you for playing !\n");

    return 0;
}