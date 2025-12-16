#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool move(int x1,int y1,int x2,int y2)
{
   if(move_valid()==0)
      {
        printf("invalid move : enter another move");
        scanf(" %d %d %d %d",&x1, &y1, &x2, &y2);
        move( x1, y1, x2, y2);

    if(islower(board[x1][y1])){ //white scope
        if(board[x1][y1]=='p'){}
         if(board[x1][y1]=='r'){
            
         }
          if(board[x1][y1]=='n'){}
           if(board[x1][y1]=='b'){}
            if(board[x1][y1]=='q'){}
             if(board[x1][y1]=='k'){}
 }





    
              if(board[x1][y1]==){}
               if(board[x1][y1]==){}
                if(board[x1][y1]==){}
                 if(board[x1][y1]==){}
   
    
        
        
        

  




}
typedef struct{
    char type;
    int posx;
    int posy;
    char colour;
    int alive;
    bool Checking;
    bool InCheck;
} piece; // added bool check on Incheck (for kings) and checking for pieces
piece pieces[32];

char** boardmaker() { //chaneged function type to return a 2d pointer for board
    // mallocated the bord inside the board functiona also increased its size for row numbers and coloumns letters from 8x8 -> 10x10
    char **board = malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; i++)
        board[i] = malloc(10 * sizeof(char));

    // initialize everything to space to avoid random garbage + edge cases ex: board[0][0]
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = ' ';

    // columns labels (a–h)
    board[0][1] = board[9][1] = 'a';
    board[0][2] = board[9][2] = 'b';
    board[0][3] = board[9][3] = 'c';
    board[0][4] = board[9][4] = 'd';
    board[0][5] = board[9][5] = 'e';
    board[0][6] = board[9][6] = 'f';
    board[0][7] = board[9][7] = 'g';
    board[0][8] = board[9][8] = 'h';

    // row labels (1–8)
    board[1][0] = board[1][9] = '8';
    board[2][0] = board[2][9] = '7';
    board[3][0] = board[3][9] = '6';
    board[4][0] = board[4][9] = '5';
    board[5][0] = board[5][9] = '4';
    board[6][0] = board[6][9] = '3';
    board[7][0] = board[7][9] = '2';
    board[8][0] = board[8][9] = '1';

    // fill board pattern (changed i,j to r,c for clarity)
    for (int r = 1; r < 9; r++)
        for (int c = 1; c < 9; c++)
            board[r][c] = ((r + c) % 2 == 0) ? '-' : '.';

    // place pieces
    for (int i = 0; i < 32; i++) {
        if (!pieces[i].alive) continue;
        board[pieces[i].posy][pieces[i].posx] = pieces[i].type; //earlier version was reversed rows in place of columns
    }
    return board;
}


int main(){
    char** board = boardmaker();

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf(" %c",board[i][j]);
            if(j==9)
            printf("\n");
        }
    }





    return 0;
}