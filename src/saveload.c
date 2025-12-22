#include <include/utility.h>
//#include "include/undo.h"
#include "include/rules.h"
#include "include/saveload.h"
#include"include/undo.h"
void save_game( char *filename, move *moves, int n)
{
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Failed to save game\n");
    }

    fwrite(&n, sizeof(int), 1, f);          // number of moves
    fwrite(moves, sizeof(move), n, f);      // all moves

    fclose(f);
    printf("Game saved successfully\n");
}
//we dont acually need this we will just call board maker
// void boardreset(char **board)
// {
//     // clear board pattern
//     for (int y = 1; y < 9; y++)
//         for (int x = 1; x < 9; x++)
//             board[y][x] = ((y + x) % 2 == 0) ? '-' : '.';

//     // place pieces (standard setup)
//     char back[] = "rnbqkbnr";

//     for (int i = 0; i < 8; i++) {
//         board[2][i+1] = 'p';
//         board[7][i+1] = 'P';

//         board[1][i+1] = back[i];
//         board[8][i+1] = toupper(back[i]);
//     }
// }
// //there is a problem
int load_game( char *filename,
              char **board,
              move *moves,int *n,int *whiteKingPos,int *blackKingPos,char*dead){
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Failed to load game\n");
        return 1;
    }

    fread(n, sizeof(int), 1, f);
    fread(moves, sizeof(move), *n, f);
    fclose(f);
    whiteKingPos[0] = 5; whiteKingPos[1] = 8;
    blackKingPos[0] = 5; blackKingPos[1] = 1;

    // Replay moves
    for (int i = 0; i < *n; i++) {
        redo(board, moves[i], whiteKingPos, blackKingPos,dead);
    }
    

    printf("Game loaded successfully\n");
    return 0;
}
void save_gametxt( char *filename, char**board)
{
    FILE *f = fopen(filename, "w+");
    if (!f) {
        printf("Failed to save game\n");
    }

    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            fputc(board[i][j],f);
        }
    }

    fclose(f);
    printf("Game saved successfully\n");
}
void load(char*filename,char**board){
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Failed to load game\n");
        return;
    }

    for(int i = 1; i < 9; i++) {
        for(int j = 1; j < 9; j++) {
            int c = fgetc(f);  // read one character
            if (c == EOF) {
                printf("Unexpected end of file\n");
                fclose(f);
                return;
            }
            board[i][j] = (char)c;
        }
    }

    fclose(f);
    printf("Game loaded successfully\n");

}