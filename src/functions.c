#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>





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
      if (board[o1][o2]!='.'||board[o1][o2]!='-') return 1;
      o2++;
      o1++;}
    if (board[x2][y2]!='.'||board[x2][y2]!='-') return 0;
    else{
      if(isupper(board[x1][y1])==isupper(board[x2][y2])) return 1;
      else return 0;}
  }
  else if ((x2-x1)<0 && (y2-y1)<0){int o1=x1,o2=y1;
    while(o1>x2 && o2>y2){
      if (board[o1][o2]!='.'||board[o1][o2]!='-') return 1;
      o2--;
      o1--;
    }
    if (board[x2][y2]!='.'||board[x2][y2]!='-') return 0;
    else{
      if(isupper(board[x1][y1])==isupper(board[x2][y2])) return 1;
      else return 0;
    }}
  else if ((x2-x1)<0 && (y2-y1)>0){
    int o1=x1,o2=y1;
    while(o1>x2 && o2<y2){
      if (board[o1][o2]!='.'||board[o1][o2]!='-') return 1;
      o2++;
      o1--;
    }
    if (board[x2][y2]!='.'||board[x2][y2]!='-') return 0;
    else{
      if(isupper(board[x1][y1])==isupper(board[x2][y2])) return 1;
      else return 0;
    }
  }
  else if ((x2-x1)>0 && (y2-y1)<0){
    int o1=x1,o2=y1;
    while(o1<x2 && o2>y2){
      if (board[o1][o2]!='.'||board[o1][o2]!='-') return 1;
      o2--;
      o1++;
    }
    if (board[x2][y2]!='.'||board[x2][y2]!='-') return 0;
    else{
      if(isupper(board[x1][y1])==isupper(board[x2][y2])) return 1;
      else return 0;
    }
  }
  


}

int main(){

board=boardmaker();

printf("%d", Rook(1,2,4,5,board));


return 0;
}