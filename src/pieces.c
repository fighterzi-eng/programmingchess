#include"include/pieces.h"
#include"include/utility.h"



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
//king v2 with castling
int king(int x1, int y1, int x2, int y2, char **board) {
    char piece = board[y1][x1];
    int is_white = islower(piece);  // 1=white (lower), 0=black (upper)
    char rook_char = is_white ? 'r' : 'R';

    // CASTLING? (2 sq horizontal from home only)
    if (abs(x2 - x1) == 2 && y2 == y1 && x1 == 5 && (y1 == 8 || y1 == 1)) {
        bool kingside = (x2 > x1);
        int rook_x = kingside ? 8 : 1;

        // Rook must be home
        if (board[y1][rook_x] != rook_char) return 1;
     
      bool *ks_right = is_white ? &wk_castle_ks : &bk_castle_ks;
      bool *qs_right = is_white ? &wk_castle_qs : &bk_castle_qs;
      if (kingside && !*ks_right) return 1;
      if (!kingside && !*qs_right) return 1;

      // Cannot castle if currently in check
      if (abs(x2 - x1) == 2 && (inCheck(x1, y1, board))) {
       return 1;
}
     

        // Path clear (hardcoded: KS f/g, QS b/c/d)
        if (kingside) {
            if (board[y1][6] != '.' && board[y1][6] != '-' || 
                board[y1][7] != '.' && board[y1][7] != '-') return 1;
        } else {
            if ((board[y1][2] != '.' && board[y1][2] != '-') ||
                (board[y1][3] != '.' && board[y1][3] != '-') ||
                (board[y1][4] != '.' && board[y1][4] != '-')) return 1;
        }

        // Sim king on PASS sq & TARGET sq (safety check)
        int dx = (x2 > x1) ? 1 : -1;
        int pass_x = x1 + dx;  // f1=6 (KS) or d1=4 (QS)

        char saved_from = piece;
        char saved_to;

        // Sim TARGET
        saved_to = board[y1][x2];
        board[y1][x2] = piece;
        board[y1][x1] = '.';
        if (inCheck(x2, y1, board)) {
            board[y1][x1] = saved_from;
            board[y1][x2] = saved_to;
            return 1;
        }
        board[y1][x1] = saved_from;
        board[y1][x2] = saved_to;

        // Sim PASS
        saved_to = board[y1][pass_x];
        board[y1][pass_x] = piece;
        board[y1][x1] = '.';
        if (inCheck(pass_x, y1, board)) {
            board[y1][x1] = saved_from;
            board[y1][pass_x] = saved_to;
            return 1;
        }
        board[y1][x1] = saved_from;
        board[y1][pass_x] = saved_to;

        return 0;  // Valid castle!
    }

    // NORMAL KING MOVE (1 sq max, any dir)
    if (x1 == x2 && y1 == y2) return 1;  // No stay put
    if (abs(x2 - x1) > 1 || abs(y2 - y1) > 1) return 1;  // Too far

    // Can't land on own piece
    char dst = board[y2][x2];
    if ((dst != '.' && dst != '-') && isupper(piece) == isupper(dst)) return 1;

    // Sim move for safety
    char saved_from = piece;
    char saved_to = dst;
    board[y2][x2] = piece;
    board[y1][x1] = '.';
    int illegal = inCheck(x2, y2, board);
    board[y1][x1] = saved_from;
    board[y2][x2] = saved_to;

    return illegal ? 1 : 0;
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
//pawn v2
int pawn(int x1, int y1, int x2, int y2, char**board){
    int direction = (isupper(board[y1][x1]) == 0) ? -1 : 1;  // White -1 (up), black +1 (down)

    if (x1 == x2 && y2 == y1 + direction && (board[y2][x2]=='-'||board[y2][x2]=='.'))
        return 0;
    
    if (abs(x2-x1)==1 && y2 == y1 + direction && isupper(board[y1][x1]) != isupper(board[y2][x2]) && !EMPTY(board[y2][x2]))
        return 0;  // Added !EMPTY to ensure capture (not empty square)

    if (x1 == x2 && y2 == y1 + 2 * direction) {
        int mid_y = y1 + direction;  // Mid square for double move
        if (isupper(board[y1][x1]) == 0 && y1 == 7 && EMPTY(board[y2][x2]) && EMPTY(board[mid_y][x2]))  
            return 0;  // White from rank 2 (y=7)

        if (isupper(board[y1][x1]) != 0 && y1 == 2 && EMPTY(board[y2][x2]) && EMPTY(board[mid_y][x2]))  
            return 0;  // Black from rank 7 (y=2)
    }
// EN PASSANT
if (abs(x2 - x1) == 1 && y2 == y1 + direction && EMPTY(board[y2][x2])) {
    if (x2 == ep_target_x && y2 == ep_target_y) {
        char opp_pawn = isupper(board[y1][x1]) ? 'p' : 'P';
        if (board[y1][x2] == opp_pawn) return 0;  // Valid EP!
    }
}
return 1;


}
//this function is the exception to a rule ,it can move pieces
// void pawnwthpromote(int x1,int y1,int x2,int y2,char**board){
//   if(pawn(x1,y1,x2,y2,board)==0){
//     if (isupper(board[y1][x1])==0){
//       if(y2==8){
//         board[y2][x2]=promote();
//         board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

//       }
//       else{
//         board[y2][x2]=board[y1][x1];
//         board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

//       }
//     }
//     else{
//       if(y2==1){
//         board[y2][x2]=toupper(promote());
//         board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

//       }
//       else{
//         board[y2][x2]=board[y1][x1];
//         board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';

//       }

//     }
//   }
// }
