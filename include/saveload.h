#ifndef SAVELOAD_H
#define SAVELOAD_H
#include "undo.h"

// Save and load functions
void save_game(const char *filename, move *moves, int n);
int load_game(const char *filename, char **board, move *moves, int *n,
              int *whiteKingPos, int *blackKingPos);
void boardreset(char **board);

#endif
