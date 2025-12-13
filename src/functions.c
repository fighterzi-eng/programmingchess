#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Quality of life
#define EMPTY(c) ((c) == '.' || (c) == '-')   // just a suggestion not yet implemented but using #define could save us space
#define WHITE(c) islower(c)
#define BLACK(c) isupper(c)

//---------------------------------------------------------------------------------------------------------------
//     Board Maker Section
//---------------------------------------------------------------------------------------------------------------

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

   
    return board;
} 
char **board;
int knight(int x1,int y1,int x2,int y2,char**board){
  if ((abs(x1-x2)==1&&abs(y1-y2)==2)||(abs(x1-x2)==2&&abs(y1-y2)==1)){
    if (board[x2][y2]=='.'||board[x2][y2]=='-') return 0;
    else{
      if(isupper(board[x1][y1])==isupper(board[x2][y2])) return 1;
      else return 0;

    }
  }
 else return 1; //forgot to return 1 if move invalid

}


//---------------------------------------------------------------------------------------------------------------
//      Piece Movement Logic Section
//---------------------------------------------------------------------------------------------------------------


int Rook(int x1, int y1, int x2, int y2, char **board) //Better and optimized Rook Validatator
{
    if (x1 != x2 && y1 != y2)
        return 1; // invalid

    char src = board[y1][x1]; //better standard than using board location everywhere
    char dst = board[y2][x2];

    int dx = (x2 > x1) - (x2 < x1);
    int dy = (y2 > y1) - (y2 < y1); //determines direction in boolean 1 up , right and -1 down,left

    int x = x1 + dx;
    int y = y1 + dy;

    while (x != x2 || y != y2) {
        if (!(board[y][x] == '.' || board[y][x] == '-'))
            return 1; // invalid
        x += dx;
        y += dy;
    }

    if (dst == '.' || dst == '-') //checks boundries
        return 0; // valid

    if (islower(src) && isupper(dst))
        return 0; // valid capture

    if (isupper(src) && islower(dst))
        return 0; // valid capture

    return 1; // invalid (own piece)
}






  




int main(){

board=boardmaker();

printf("%d", Rook(1,2,4,5,board));


return 0;
}