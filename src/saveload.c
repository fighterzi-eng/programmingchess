#include "include/saveload.h"


extern int ep_target_x, ep_target_y;
extern bool wk_castle_ks, wk_castle_qs, bk_castle_ks, bk_castle_qs;
extern int deadn;

void save_game_bin(int* n, char *dead,move* moves) {
    char filename[64];
    printf("Enter filename to save example: savefile.bin ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "wb");
    if (!f) return;

    // Save state
    fwrite(dead, sizeof(char), 32, f);
    fwrite(n, sizeof(int), 1, f);
    fwrite(&deadn, sizeof(int), 1, f);
    fwrite(&wk_castle_ks, sizeof(bool), 1, f);
    fwrite(&wk_castle_qs, sizeof(bool), 1, f);
    fwrite(&bk_castle_ks, sizeof(bool), 1, f);
    fwrite(&bk_castle_qs, sizeof(bool), 1, f);
    fwrite(&ep_target_x, sizeof(int), 1, f);
    fwrite(&ep_target_y, sizeof(int), 1, f);

    // Save history
    fwrite(moves, sizeof(move), *n, f);
    fclose(f);
    printMoveHistoryRaw(moves,*n);
}

int load_game_bin(char **board, int *n, int *whitekingpos, int *blackkingpos, char *dead,int* ep_target_x,int* ep_target_y,
bool *wk_castle_ks, bool* wk_castle_qs,
bool* bk_castle_ks , bool* bk_castle_qs,move *moves ) {
    char filename[64];
    printf("Enter filename to load: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Load failed!\n");
        return 0;
    }
    fread(dead, sizeof(char), 32, f);
    fread(n, sizeof(int), 1, f);
    fread(&deadn, sizeof(int), 1, f);
    fread(wk_castle_ks, sizeof(bool), 1, f);
    fread(wk_castle_qs, sizeof(bool), 1, f);
    fread(bk_castle_ks, sizeof(bool), 1, f);
    fread(bk_castle_qs, sizeof(bool), 1, f);
    fread(ep_target_x, sizeof(int), 1, f);
    fread(ep_target_y, sizeof(int), 1, f);
    fread(moves, sizeof(move), *n, f);
    fclose(f);
    printMoveHistoryRaw(moves,*n);

    for (int i = 0; i < *n; i++) {
        moving(&moves[i],board,dead);
    }
       
    // CRITICAL: Synchronize the king pointers
    updateKingPositions(board, whitekingpos, blackkingpos);

    return 1;
}