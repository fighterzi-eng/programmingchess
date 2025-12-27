#ifndef MOVE_H
#define MOVE_H

typedef struct {
    int x1, y1, x2, y2;
    char p1, p2, promotion;
    int wkx_before, wky_before, bkx_before, bky_before;
    
    // Specials
    int rook_x1, rook_x2;
    char r_p1;
    char ep_captured_p;
    
    // NEW: State preservation for Load/Undo
    int wk_ks, wk_qs, bk_ks, bk_qs; // Castling rights BEFORE this move
    int ep_tx, ep_ty;               // En Passant target BEFORE this move
    int n;                          // Turn index
} move;
#endif