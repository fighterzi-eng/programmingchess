#include"include/undo.h"

move moves[1024];
void printMoveHistoryRaw(move *moves, int total_moves) {
    if (total_moves <= 0) {
        printf("No moves in history.\n");
        return;
    }

    printf("\n======= RAW MOVE HISTORY =======\n");

    for (int i = 0; i < total_moves; i++) {
        move *m = &moves[i];

        printf("Move %d:\n", i + 1);
        printf("  From: (%d, %d)\n", m->x1, m->y1);
        printf("  To  : (%d, %d)\n", m->x2, m->y2);
        printf("  p1  : '%c'\n", m->p1 ? m->p1 : '.');
        printf("  p2  : '%c'\n", m->p2 ? m->p2 : '.');
        printf("  promo: '%c'\n", m->promotion ? m->promotion : '.');

        printf("  Castling: rook_x1=%d rook_x2=%d rook_piece='%c'\n",
               m->rook_x1, m->rook_x2,
               m->r_p1 ? m->r_p1 : '.');

        printf("  EnPassant captured: '%c'\n",
               m->ep_captured_p ? m->ep_captured_p : '.');

        printf("  King before move: WK(%d,%d) BK(%d,%d)\n",
               m->wkx_before, m->wky_before,
               m->bkx_before, m->bky_before);

        printf("  Castling rights before: WK(%d,%d) BK(%d,%d)\n",
               m->wk_ks, m->wk_qs, m->bk_ks, m->bk_qs);

        printf("  EP target before: (%d,%d)\n",
               m->ep_tx, m->ep_ty);

        printf("  Turn index stored: %d\n", m->n);

        printf("--------------------------------\n");
    }

    printf("================================\n");
}
void undo(char **board, move m, int *whitekingpos, int *blackkingpos, char *dead) {
    // 1. Restore Pieces
    board[m.y1][m.x1] = m.p1;
    board[m.y2][m.x2] = m.p2;

    // 2. Undo Rook (Castling)
    if (m.rook_x1 != 0) {
        char empty_r2 = ((m.y1 + m.rook_x2) % 2 == 0) ? '-' : '.';
        board[m.y1][m.rook_x1] = m.r_p1;
        board[m.y1][m.rook_x2] = empty_r2;
    }

    // 3. Undo En Passant capture
    if (m.ep_captured_p != '\0') {
        board[m.y1][m.x2] = m.ep_captured_p;
        deadn--; // Important: decrement dead counter
    } else if (m.p2 != '.' && m.p2 != '-') {
        deadn--; // Regular capture undo
    }

    // 4. RESTORE FLAGS
    wk_castle_ks = m.wk_ks; wk_castle_qs = m.wk_qs;
    bk_castle_ks = m.bk_ks; bk_castle_qs = m.bk_qs;
    ep_target_x = m.ep_tx;  ep_target_y = m.ep_ty;

    // 5. Restore King Positions
    whitekingpos[0] = m.wkx_before; whitekingpos[1] = m.wky_before;
    blackkingpos[0] = m.bkx_before; blackkingpos[1] = m.bky_before;

}

void redo(char **board, move m, int whitekingpos[2], int blackkingpos[2], char *dead) {
    char empty_from = ((m.y1 + m.x1) % 2 == 0) ? '-' : '.';
    board[m.y1][m.x1] = empty_from;
    char ch = (m.promotion != '0') ? m.promotion : m.p1;
    board[m.y2][m.x2] = ch;
    // Redo rook
    if (m.rook_x1 != 0) {
        char empty_r1 = ((m.y1 + m.rook_x1) % 2 == 0) ? '-' : '.';
        board[m.y1][m.rook_x1] = empty_r1;
        board[m.y1][m.rook_x2] = m.r_p1;
    }
    // Redo ep: clear captured
    if (m.ep_captured_p != '\0') {
        char empty_cap = ((m.y1 + m.x2) % 2 == 0) ? '-' : '.';
        board[m.y1][m.x2] = empty_cap;
    }
    if (m.ep_captured_p != '\0') {
    deadn++;
    dead[deadn] = m.ep_captured_p;
    } else if (m.p2 != '.' && m.p2 != '-') {
    deadn++;
    dead[deadn] = m.p2;
}

    // BETTER FIX: Manually kill flags if King/Rook moves
    if (tolower(m.p1) == 'k') {
        if (islower(m.p1)) { wk_castle_ks = false; wk_castle_qs = false; }
        else               { bk_castle_ks = false; bk_castle_qs = false; }
    }
    else if (tolower(m.p1) == 'r') {
        // Logic to kill specific side castling if rook moves
        if (islower(m.p1) && m.y1 == 8 && m.x1 == 1) wk_castle_qs = false;
        if (islower(m.p1) && m.y1 == 8 && m.x1 == 8) wk_castle_ks = false;
        if (isupper(m.p1) && m.y1 == 1 && m.x1 == 1) bk_castle_qs = false;
        if (isupper(m.p1) && m.y1 == 1 && m.x1 == 8) bk_castle_ks = false;
    }


    // Kingpos update...
    // Only update King pointers if the piece moved was actually a King
if (tolower(m.p1) == 'k') { 
    if (isupper(m.p1)) { // Black King
        blackkingpos[0] = m.x2;
        blackkingpos[1] = m.y2;
    } else { // White King
        whitekingpos[0] = m.x2;
        whitekingpos[1] = m.y2;
    }
}
}

void addmove(int x1, int y1, char p1, int x2, int y2, char p2, int n, char promotion, int *wk, int *bk) {
    moves[n].x1 = x1; moves[n].y1 = y1;
    moves[n].x2 = x2; moves[n].y2 = y2;
    moves[n].p1 = p1; moves[n].p2 = p2;
    moves[n].promotion = promotion;
    
    // King Positions
    moves[n].wkx_before = wk[0]; moves[n].wky_before = wk[1];
    moves[n].bkx_before = bk[0]; moves[n].bky_before = bk[1];

    // Save CURRENT flags into the move struct before they get changed by 'moving'
    moves[n].wk_ks = wk_castle_ks; moves[n].wk_qs = wk_castle_qs;
    moves[n].bk_ks = bk_castle_ks; moves[n].bk_qs = bk_castle_qs;
    moves[n].ep_tx = ep_target_x;  moves[n].ep_ty = ep_target_y;

    moves[n].rook_x1 = 0; moves[n].rook_x2 = 0;
    moves[n].r_p1 = '\0';
    moves[n].ep_captured_p = '\0';
    moves[n].n = n;
}
