#include <stdio.h>
#include "undo.h"
#include "rules.h"
#include "saveload.h"


void save_game(const char *filename, move *moves, int n)
{
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Failed to save game\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, f);          // number of moves
    fwrite(moves, sizeof(move), n, f);      // all moves

    fclose(f);
    printf("Game saved successfully\n");
}

void boardreset(char **board)
{
    // clear board pattern
    for (int y = 1; y < 9; y++)
        for (int x = 1; x < 9; x++)
            board[y][x] = ((y + x) % 2 == 0) ? '-' : '.';

    // place pieces (standard setup)
    char back[] = "rnbqkbnr";

    for (int i = 0; i < 8; i++) {
        board[2][i+1] = 'p';
        board[7][i+1] = 'P';

        board[1][i+1] = back[i];
        board[8][i+1] = toupper(back[i]);
    }
}

int load_game(const char *filename,
              char **board,
              move *moves,
              int *n,
              int *whiteKingPos,
              int *blackKingPos)
{
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Failed to load game\n");
        return 1;
    }

    fread(n, sizeof(int), 1, f);
    fread(moves, sizeof(move), *n, f);
    fclose(f);

    // Reset board to initial position
    boardreset(board);   // IMPORTANT: you need this function

    // Initial king positions
    whiteKingPos[0] = 5; whiteKingPos[1] = 8;
    blackKingPos[0] = 5; blackKingPos[1] = 1;

    // Replay moves
    for (int i = 0; i < *n; i++) {
        redo(board, moves[i], whiteKingPos, blackKingPos);
    }

    printf("Game loaded successfully\n");
    return 0;
}
