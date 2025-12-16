//we need to split this file into multiple files because its too large about 400 lines
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
    // mallocated the board inside the board functiona also increased its size for row numbers and coloumns letters from 8x8 -> 10x10
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
//---------------------------------------------------------------------------------------------------------------
//      Piece Movement Logic Section
//---------------------------------------------------------------------------------------------------------------

int movevalidator(int x1,int y1,int x2,int y2,char**board){
  char piece=board[y1][x1];
  piece=toupper(piece);
  switch (piece)
  {
  case 'K':
    return king(x1,y1,x2,y2,board);
   
    break;
  case 'P':
    return pawn(x1,y1,x2,y2,board);
    break;
  case 'R':
    return rook(x1,y1,x2,y2,board);
    break;
  case 'N':
    return knight(x1,y1,x2,y2,board);
    break;
  case 'B':
    return bishop(x1,y1,x2,y2,board);
    break;
  case 'Q':
    if(bishop(x1,y1,x2,y2,board)==0||rook(x1,y1,x2,y2,board)==0) return 0;
    else return 1;
    break;
  
  default:
    printf("invalid move");
    return 1;
    break;
  }
}
char promote(){
  char ch;
  scanf(" %c",&ch);
  switch (ch)
  {
  case 'r':
    return ch;
    break;
  case 'n':
    return ch;
    break;
  case 'b':
    return ch;
    break;
  case 'q':
    return ch;
    break;
  
  
  default:
  printf("invalid enter again");
  return promote();
    break;
  }
}
int pawn(int x1,int y1,int x2,int y2,char**board){
  int direction = (isupper(board[y1][x1])==0) ? 1 : -1;

    if (x1 == x2 && y2 == y1 + direction && (board[y2][x2]=='-'||board[y2][x2]=='.'))
        return 0;
    if (abs(x2-x1)==1 && y2 == y1 + direction && isupper(board[y1][x1])!=isupper(board[y2][x2]))
        return 0;

    if (x1 == x2 &&
        y2 == y1 + 2 * direction) {

        if (isupper(board[y1][x1])==0 && y1 == 2&& (board[y2][x2]=='-'||board[y2][x2]=='.'))  
            return 0;

        if (isupper(board[y1][x1])!=0 && y1 == 7&& (board[y2][x2]=='-'||board[y2][x2]=='.'))  
            return 0;
    }

    return 1;
}
//this function is the exception to a rule ,it can move pieces
int pawnwthpromote(int x1,int y1,int x2,int y2,char**board){
  if(pawn(x1,y1,x2,y2,board)==0){
    if (isupper(board[y1][x1])==0){
      if(y2==8){
        board[y2][x2]=promote();
        board[x1][y1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
      else{
        board[y2][x2]=board[x1][y1];
        board[x1][y1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
    }
    else{
      if(y2==1){
        board[y2][x2]=toupper(promote());
        board[x1][y1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
      else{
        board[y2][x2]=board[x1][y1];
        board[x1][y1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }

    }
  }
}

//this is a basic way of checking danger and it will work but its not efficent
//i can make it more efficent if i can track each piece
//return 1 if danger,0 if safe
/*int checkdanger(int x,int y,char**board){ Danger Checker V1
  for(int i=1;i<9;i++){
    for(int j=1;j<9;j++){
      if((board[i][j]=='-'||board[i][j]=='.')) continue;
      if(isupper(board[y][x])==isupper(board[i][j])) continue;
      if (movevalidator(i,j,x,y,board)==0) return 1;
    }

  }
  return 0;
}*/ 

// V2 Uses the earlier #defines for simplicity

int inside(int x, int y) { //useful
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}
int inCheck(int kx, int ky, char **board) //1 = Danger , 0 = safe
{
    char king = board[ky][kx];
    int whiteKing = WHITE(king); //determines colour

  int dxR[4] = {1, -1, 0, 0};
    int dyR[4] = {0, 0, 1, -1};

    for (int d = 0; d < 4; d++) {
        int x = kx + dxR[d];
        int y = ky + dyR[d];

        while (inside(x, y)) { //Checks for queen or rook
            char p = board[y][x];

            if (!EMPTY(p)) {
                if (whiteKing && BLACK(p) && (p == 'R' || p == 'Q'))
                    return 1;
                if (!whiteKing && WHITE(p) && (p == 'r' || p == 'q'))
                    return 1;
                break;
            }
            x += dxR[d];
            y += dyR[d];
        }
    }
   int dxB[4] = {1, 1, -1, -1};
   int dyB[4] = {1, -1, 1, -1};
 
 for (int d = 0; d < 4; d++) {// queen or bishop
        int x = kx + dxB[d];
        int y = ky + dyB[d];

        while (inside(x, y)) {
            char p = board[y][x];

            if (!EMPTY(p)) {
                if (whiteKing && BLACK(p) && (p == 'B' || p == 'Q'))
                    return 1;
                if (!whiteKing && WHITE(p) && (p == 'b' || p == 'q'))
                    return 1;
                break;
            }
            x += dxB[d];
            y += dyB[d];
        }
    }
    int kdx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int kdy[8] = { 1, 2,  2,  1, -1, -2,-2,-1 };

    for (int i = 0; i < 8; i++) {//Danger of knight
        int x = kx + kdx[i];
        int y = ky + kdy[i];

        if (inside(x, y)) {
            char p = board[y][x];
            if (whiteKing && p == 'N') return 1;
            if (!whiteKing && p == 'n') return 1;
        }
    }
if (whiteKing) {//NEEDS CAREFUL DEBUGGING LATER NOT 100% sure it even works
        // black pawns attack DOWN
        int px[2] = {kx - 1, kx + 1};
        int py = ky + 1;

        for (int i = 0; i < 2; i++)
            if (inside(px[i], py) && board[py][px[i]] == 'P')
                return 1;
    } else {
        // white pawns attack UP
        int px[2] = {kx - 1, kx + 1};
        int py = ky - 1;

        for (int i = 0; i < 2; i++)
            if (inside(px[i], py) && board[py][px[i]] == 'p')
                return 1;
    }
    //Checks for enemy king 
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            int x = kx + dx;
            int y = ky + dy;

            if (inside(x, y)) {
                char p = board[y][x];
                if (whiteKing && p == 'K') return 1;
                if (!whiteKing && p == 'k') return 1;
            }
        }
    }
// if every thing ok returns safe
    return 0;
}

//Rook
int rook(int x1, int y1, int x2, int y2, char **board) //Better and optimized Rook Validatator
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
//knight
int knight(int x1,int y1,int x2,int y2,char**board){
  if ((abs(x1-x2)==1&&abs(y1-y2)==2)||(abs(x1-x2)==2&&abs(y1-y2)==1)){
    if (board[y2][x2]=='.'||board[y2][x2]=='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;

    }
  }
}
//bishop
int bishop(int x1, int y1, int x2, int y2, char **board) //Better and optimized Bishop Validatator
{
    if (abs(x1 - x2) != abs(y1 - y2))
        return 1;

    int dx = (x2 > x1) ? 1 : -1;
    int dy = (y2 > y1) ? 1 : -1;

    int x = x1 + dx;
    int y = y1 + dy;

    while (x != x2 && y != y2) {
        if (board[y][x] != '.' && board[y][x] != '-')
            return 1;
        x += dx;
        y += dy;
    }

    if (board[y2][x2] == '.' || board[y2][x2] == '-')
        return 0;

    if (isupper(board[y1][x1]) == isupper(board[y2][x2]))
        return 1;

    return 0;
}
//king
int king(int x1, int y1, int x2, int y2, char **board)
{
    // Must move
    if (x1 == x2 && y1 == y2)
        return 1;

    // King moves max 1 square
    if (abs(x1 - x2) > 1 || abs(y1 - y2) > 1)
        return 1;

    // Can't capture own piece
    if (board[y2][x2] != '.' && board[y2][x2] != '-') {
        if (isupper(board[y1][x1]) == isupper(board[y2][x2]))
            return 1;
    }

    // --- simulate move ,good practice to check validity of move --- 
    char savedFrom = board[y1][x1];
    char savedTo   = board[y2][x2];

    board[y2][x2] = board[y1][x1];
    board[y1][x1] = '.';

    // Check if king would be in check
    int illegal = inCheck(x2, y2, board);

    // --- undo move ---
    board[y1][x1] = savedFrom;
    board[y2][x2] = savedTo;

    if (illegal)
        return 1;

    return 0;
}
//Queen Easiest in implementation
int queen(int x1,int y1,int x2,int y2,char**board){
  if(bishop(x1,y1,x2,y2,board)==0||rook(x1,y1,x2,y2,board)==0) return 0;
  else return 1;
}
int main(){

board=boardmaker();

printf("%d", Rook(1,2,4,5,board));


return 0;
}