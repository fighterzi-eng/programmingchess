#include"include/utility.h"
int inside(int x, int y) { //useful
    return (x >= 1 && x < 9 && y >= 1 && y < 9);
}
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
void boardprint(char**board){
    for(int i=8;i>0;i--){
        for(int j=1;j<9;j++){
            printf("%c",board[i][j]);

        }
        printf("\n");
    }
}
//this is a basic way of checking danger and it will work but its not efficent
//i can make it more efficent if i can track each piece
//return 1 if danger,0 if safe
/*int incheck(int x,int y,char**board){ Danger Checker V1
  for(int i=1;i<9;i++){
    for(int j=1;j<9;j++){
      if((board[i][j]=='-'||board[i][j]=='.')) continue;
      if(isupper(board[y][x])==isupper(board[i][j])) continue;
      if (movevalidator(i,j,x,y,board)==0) return 1;
    }

  }
  return 0;
}*/ 
