#include"include/utility.h"
#include"include/undo.h"

extern bool wk_castle_ks, wk_castle_qs, bk_castle_ks, bk_castle_qs;

int inside(int x, int y) { //useful
    return (x >= 1 && x < 9 && y >= 1 && y < 9);
}
char** boardmaker(int *whitekingpos, int *blackkingpos) { //updated to include pieces
    char **board = malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; i++)
        board[i] = malloc(10 * sizeof(char));

    // Initialize everything to space to avoid garbage
    for (int r = 0; r < 10; r++)
        for (int c = 0; c < 10; c++)
            board[r][c] = ' ';

    // Column labels (optional)
    char cols[] = "abcdefgh";
    for (int i = 0; i < 8; i++) {
        board[0][i+1] = cols[i];  // top
        board[9][i+1] = cols[i];  // bottom
    }

    // Row labels (optional)
    for (int i = 1; i <= 8; i++) {
        board[i][0] = '0' + (9-i);  // left
        board[i][9] = '0' + (9-i);  // right
    }

    // Fill board pattern
    for (int y = 1; y < 9; y++)
        for (int x = 1; x < 9; x++)
            board[y][x] = ((y + x) % 2 == 0) ? '-' : '.';

// Black pieces (top, rank 8)
char blackBack[] = "RNBQKBNR";
for (int i = 0; i < 8; i++) {
    board[8][i+1] = blackBack[i];
    board[7][i+1] = 'P';
}

// White pieces (bottom, rank 1)
char whiteBack[] = "rnbqkbnr";
for (int i = 0; i < 8; i++) {
    board[1][i+1] = whiteBack[i];
    board[2][i+1] = 'p';
}

       // Set king positions automatically
    if (whitekingpos != NULL) {
        whitekingpos[0] = 5; // x
        whitekingpos[1] = 8; // y
    }
    if (blackkingpos != NULL) {
        blackkingpos[0] = 5; // x
        blackkingpos[1] = 1; // y
    }
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
if (whiteKing) {  // White king, check for black 'P' above (ky-1)
    int px[2] = {kx - 1, kx + 1};
    int py = ky - 1;
    for (int i = 0; i < 2; i++)
        if (inside(px[i], py) && board[py][px[i]] == 'P')
            return 1;
} else {  // Black king, check for white 'p' below (ky + 1)
    int px[2] = {kx - 1, kx + 1};
    int py = ky + 1;
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
    for(int i=10;i>0;i--){
        for(int j=0;j<10;j++){
            printf(" %c",board[i][j]);

        }
        printf("\n");
    }
}
// added move parser

int parseMove(char *move, int *x1, int *y1, int *x2, int *y2) {
    if (strlen(move) != 4) return 1;  // Exactly 4 chars for e2e4 style notation

    if (move[0] < 'a' || move[0] > 'h' ||
        move[2] < 'a' || move[2] > 'h' ||
        move[1] < '1' || move[1] > '8' ||
        move[3] < '1' || move[3] > '8')
        return 1;  // Invalid chars

    *x1 = (move[0] - 'a') + 1;
    *y1 = 9 - (move[1] - '0');
    *x2 = (move[2] - 'a') + 1;
    *y2 = 9 - (move[3] - '0');

    return 0;  // Success!
}
void updateKingPositions(char** board, int* whitekingpos, int* blackkingpos) {
    for (int y = 1; y < 9; y++) {
        for (int x = 1; x < 9; x++) {
            if (board[y][x] == 'k') {
                whitekingpos[0] = x;
                whitekingpos[1] = y;
            } else if (board[y][x] == 'K') {
                blackkingpos[0] = x;
                blackkingpos[1] = y;
            }
        }
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
