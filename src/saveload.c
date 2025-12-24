#include "include/saveload.h"
#include "include/undo.h"
#include "include/utility.h"
#include <stdio.h>

extern int ep_target_x, ep_target_y;
extern bool wk_castle_ks, wk_castle_qs, bk_castle_ks, bk_castle_qs;
extern int deadn;
extern move moves[1024];

void save_game_bin(int n) {
    char filename[64];
    printf("Enter filename to save example: savefile.bin ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "wb");
    if (!f) return;

    // Save state
    fwrite(&n, sizeof(int), 1, f);
    fwrite(&deadn, sizeof(int), 1, f);
    fwrite(&wk_castle_ks, sizeof(bool), 1, f);
    fwrite(&wk_castle_qs, sizeof(bool), 1, f);
    fwrite(&bk_castle_ks, sizeof(bool), 1, f);
    fwrite(&bk_castle_qs, sizeof(bool), 1, f);
    fwrite(&ep_target_x, sizeof(int), 1, f);
    fwrite(&ep_target_y, sizeof(int), 1, f);

    // Save history
    fwrite(moves, sizeof(move), n, f);
    fclose(f);
}

int load_game_bin(char **board, int *n, int *whitekingpos, int *blackkingpos, char *dead) {
    char filename[64];
    printf("Enter filename to load: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Load failed!\n");
        return 0;
    }

    fread(n, sizeof(int), 1, f);
    fread(&deadn, sizeof(int), 1, f);
    fread(&wk_castle_ks, sizeof(bool), 1, f);
    fread(&wk_castle_qs, sizeof(bool), 1, f);
    fread(&bk_castle_ks, sizeof(bool), 1, f);
    fread(&bk_castle_qs, sizeof(bool), 1, f);
    fread(&ep_target_x, sizeof(int), 1, f);
    fread(&ep_target_y, sizeof(int), 1, f);
    fread(moves, sizeof(move), *n, f);
    fclose(f);

    // RESET EXISTING BOARD MANUALLY (No malloc here!)

    for (int y = 1; y < 9; y++) {
    for (int x = 1; x < 9; x++) {
        board[y][x] = ((y + x) % 2 == 0) ? '-' : '.';
    }
}
char back[] = "rnbqkbnr";
for (int i = 0; i < 8; i++) {
    board[8][i+1] = back[i];           // White back rank (bottom)
    board[7][i+1] = 'p';               // White pawns
    board[1][i+1] = toupper(back[i]);  // Black back rank (top)
    board[2][i+1] = 'P';               // Black pawns
}

    // REPLAY THE MOVES
    for (int i = 0; i < *n; i++) {
        // Simple move application
        char piece = (moves[i].promotion != '0') ? moves[i].promotion : moves[i].p1;
        board[moves[i].y1][moves[i].x1] = ((moves[i].y1 + moves[i].x1) % 2 == 0) ? '-' : '.';
        board[moves[i].y2][moves[i].x2] = piece;

        // Restore Rook if it was a castle
        if (moves[i].rook_x1 != 0) {
            board[moves[i].y1][moves[i].rook_x2] = moves[i].r_p1;
            board[moves[i].y1][moves[i].rook_x1] = ((moves[i].y1 + moves[i].rook_x1) % 2 == 0) ? '-' : '.';
        }
        // Remove pawn if it was En Passant
        if (moves[i].ep_captured_p != '\0') {
            board[moves[i].y1][moves[i].x2] = ((moves[i].y1 + moves[i].x2) % 2 == 0) ? '-' : '.';
        }
    }

    // CRITICAL: Synchronize the king pointers
    updateKingPositions(board, whitekingpos, blackkingpos);

    return 1;
}