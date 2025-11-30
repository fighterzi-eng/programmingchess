#include<stdio.h>
typedef struct{
    char name;
    int posx;
    int posy;
    char colour;
    int alive;
} piece;
piece pieces[32];
char board[8][8];
void boardmaker(){
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if ((i+j)%2==0) board[i][j]='.';
            else board[i][j]='-';

        }

    }
    for(int i=0;i<32;i++){
        if (pieces[i].alive==0) continue;
        board[pieces[i].posx][pieces[i].posy]=pieces[i].name;

    }
}


int main(){





    return 0;
}