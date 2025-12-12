//we need to split this file into multiple files because its too large about 400 lines
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//this is a basic way of checking danger and it will work but its not efficent
//i can make it more efficent if i can track each piece
//return 1 if danger,0 if safe
int checkdanger(int x,int y,char**board){
  for(int i=1;i<9;i++){
    for(int j=1;j<9;j++){
      if((board[i][j]=='-'||board[i][j]=='.')) continue;
      if(isupper(board[y][x])==isupper(board[i][j])) continue;
      if (movevalidator(i,j,x,y,board)==0) return 1;
    }

  }
  return 0;
}
char **board;
char dead[30];
//not defined yet only a declared prototype
int king(int x1,int y1,int x2,int y2,char**board);
//the excution of this function will be base on the output of the mov e validator if it returned 1 aka false
//the while loop will continue without incrementing the turn 
void move(int x1,int y1,int x2,int y2,char**board,char*dead){
  static int deadn=0;
  if (!(board[y1][x1]=='-'||board[y1][x1]=='.')){
    dead[deadn]=board[y2][x2];
    deadn++;

  }
  board[y2][x2]=board[x1][y1];
  board[x1][y1] = ((y1 + x1) % 2 == 0) ? '-' : '.';


}
//the base for the move validator(prototype)
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
  scanf("%c",&ch);
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

int knight(int x1,int y1,int x2,int y2,char**board){
  if ((abs(x1-x2)==1&&abs(y1-y2)==2)||(abs(x1-x2)==2&&abs(y1-y2)==1)){
    if (board[y2][x2]=='.'||board[y2][x2]=='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;

    }
  }


}

int Rook(int x1,int y1,int x2,int y2,char**board){

if(!(x1==x2||y1==y2))return 1;


if(islower(board[y1][x1])==1){ //white rook
  // we are going to remove this condition and implement it in the global move validator instaead of copying and pating it everywhaere
  if(x1<=8 && x1>=1 &&x2<=8 && x2>=1 &&y1<=8 && y1>=1 &&y2<=8 && y2>=1){
    int x3 =x2-x1;
    if(x3==0){
        int y3=y2-y1;
     if(y3>0){
      for(int i=y1;i<y2;i++)
    if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 0;
     if(islower(board[y2][x2]==1))
      return 1;
    if(x3>0){
      for(int i=y1;i<y2;i++)
    if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 0;
     if(islower(board[y2][x2]==1))
      return 1;
}
   if(x3>0){
      for(int i=x1;i>x2;i--)
      if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 0;
     if(islower(board[y2][x2]==1))
      return 1;
  }
    }  
   if(x3>0){
      for(int i=x1;i<x2;i++)
      if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 0;
     if(islower(board[y2][x2]==1))
      return 1;

}
   if(x3>0){
      for(int i=x1;i>x2;i--)
    if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 0;
     if(islower(board[y2][x2]==1))
      return 1;
  
  }}}}
if(isupper(board[y1][x1])==1){ //black rock
  if(x1<=8 && x1>=1 &&x2<=8 && x2>=1 &&y1<=8 && y1>=1 &&y2<=8 && y2>=1){
    int x3 =x2-x1;
      if(x3==0){
        int y3=y2-y1;
     if(y3>0){
      for(int i=y1;i<y2;i++)
     if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 1;
     if(islower(board[y2][x2]==1))
      return 0;
    if(x3>0){
      for(int i=y1;i<y2;i++)
     if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 1;
     if(islower(board[y2][x2]==1))
      return 0;

}
   if(x3>0){
      for(int i=x1;i>x2;i--)
     if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 1;
     if(islower(board[y2][x2]==1))
      return 0;
  
  }
    }  
   if(x3>0){
      for(int i=x1;i<x2;i++)
      if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2]==1))
      return 1;
     if(islower(board[y2][x2]==1))
      return 0;
}
   if(x3>0){
      for(int i=x1;i>x2;i--)
    if(!(board[y1][i]=='.'||board[y1][i]=='-'))
      return 1;
     if(isupper(board[y2][x2])==1)
      return 1;
     if(islower(board[y2][x2])==1)
      return 0;
  }}}}
 return 0;
}

int bishop(int x1,int y1,int x2,int y2,char**board){

  if (!(abs(x1-x2)==abs(y1-y2))) return 1;
  if ((x2-x1)>=0 && (y2-y1)>=0){
    int o1=x1,o2=y1;
    while(o1<x2 && o2<y2){
      if (board[o2][o1]!='.'||board[o2][o1]!='-') return 1;
      o2++;
      o1++;}
    if (board[y2][x2]!='.'||board[y2][x2]!='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;}
  }
  else if ((x2-x1)<0 && (y2-y1)<0){int o1=x1,o2=y1;
    while(o1>x2 && o2>y2){
      if (board[o2][o1]!='.'||board[o2][o1]!='-') return 1;
      o2--;
      o1--;
    }
    if (board[y2][x2]!='.'||board[y2][x2]!='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;
    }}
  else if ((x2-x1)<0 && (y2-y1)>0){
    int o1=x1,o2=y1;
    while(o1>x2 && o2<y2){
      if (board[o2][o1]!='.'||board[o2][o1]!='-') return 1;
      o2++;
      o1--;
    }
    if (board[y2][x2]!='.'||board[y2][x2]!='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;
    }
  }
  else if ((x2-x1)>0 && (y2-y1)<0){
    int o1=x1,o2=y1;
    while(o1<x2 && o2>y2){
      if (board[o2][o1]!='.'||board[o2][o1]!='-') return 1;
      o2--;
      o1++;
    }
    if (board[y2][x2]!='.'||board[y2][x2]!='-') return 0;
    else{
      if(isupper(board[y1][x1])==isupper(board[y2][x2])) return 1;
      else return 0;
    }
  }
  


}

int main(){

board=boardmaker();

printf("%d", Rook(1,2,4,5,board));


return 0;
}