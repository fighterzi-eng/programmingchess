#include"include/rules.h"
int endgamecheck(int*kingpos,char**board){
  int kx=kingpos[0];
  int ky=kingpos[1];
  for (int i=1;i<9;i++){
    for (int j=1;j<9;j++){
      if (EMPTY(board[i][j])) continue;
      if (isupper(board[i][j])!=isupper(board[ky][kx])) continue;
      else{
         for (int k=1;k<9;k++){
    for (int p=1;p<9;p++){
      if (movevalidator(j,i,k,p,board,kingpos)==0) return 0;
    }}

      }
    
  }

  }
  if (inCheck(kx,ky,board)==1) return 1;//means checkmate
  else return 2;//means stale mate
}
int movevalidator(int x1,int y1,int x2,int y2,char**board,int*kingpos){
  char piece=board[y1][x1];
  piece=toupper(piece);
  int validity=0;
  int kx=kingpos[0];
  int ky=kingpos[1];
  switch (piece)
  {
  case 'K':
    validity= king(x1,y1,x2,y2,board);
    if(validity==0){
      kx=x2;
      ky=y2;
    }
   
    break;
  case 'P':
    validity= pawn(x1,y1,x2,y2,board);
    break;
  case 'R':
    validity= rook(x1,y1,x2,y2,board);
    break;
  case 'N':
    validity= knight(x1,y1,x2,y2,board);
    break;
  case 'B':
    validity= bishop(x1,y1,x2,y2,board);
    break;
  case 'Q':
    if(bishop(x1,y1,x2,y2,board)==0||rook(x1,y1,x2,y2,board)==0) validity= 0;
    else validity= 1;
    break;
  
  default:
    printf("invalid piece");
    validity= 1;
    break;
  }
  //this part check if the king is in danger after the move ,i took abit from your king function underneath
  if (validity==0){
  char savedFrom = board[y1][x1];
  char savedTo   = board[y2][x2];

  board[y2][x2] = board[y1][x1];
  board[y1][x1] = '.';

    // Check if king would be in check
  int illegal = inCheck(kx, ky, board);

    // --- undo move ---
  board[y1][x1] = savedFrom;
  board[y2][x2] = savedTo;

  if (illegal) return 1;
  return validity;}
  return validity;
}
void moving(int x1,int y1,int x2,int y2,char**board,char*dead){
  static int deadn=0;
  if (!(board[y1][x1]=='-'||board[y1][x1]=='.')){
    dead[deadn]=board[y2][x2];
    deadn++;

  }
  board[y2][x2]=board[y1][x1];
  board[y1][x1] = ((y1 + x1) % 2 == 0) ? '-' : '.';


}