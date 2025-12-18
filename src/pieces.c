#include"include/pieces.h"
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
  return 1;
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

        if (isupper(board[y1][x1])==0 && y1 == 2&& (board[y2][x2]=='-'||board[y2][x2]=='.')&& (board[y2-1][x2]=='-'||board[y2-1][x2]=='.'))  
            return 0;

        if (isupper(board[y1][x1])!=0 && y1 == 7&& (board[y2][x2]=='-'||board[y2][x2]=='.')&& (board[y2-1][x2]=='-'||board[y2-1][x2]=='.'))  
            return 0;
    }

    return 1;
}
//this function is the exception to a rule ,it can move pieces
void pawnwthpromote(int x1,int y1,int x2,int y2,char**board){
  if(pawn(x1,y1,x2,y2,board)==0){
    if (isupper(board[y1][x1])==0){
      if(y2==8){
        board[y2][x2]=promote();
        board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
      else{
        board[y2][x2]=board[y1][x1];
        board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
    }
    else{
      if(y2==1){
        board[y2][x2]=toupper(promote());
        board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }
      else{
        board[y2][x2]=board[y1][x1];
        board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

      }

    }
  }
}
