#include"include/undo.h"
#include"include/utility.h"
#include "include/rules.h"
/*typedef struct 
{
    int x1;
    int y1;
    char p1;
    int x2;
    int y2;
    char p2;

    
}move;*/ //we already have this in the header file cant define it twice

move moves[1024];
// Fixed Undo to restore flags
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
    // Kingpos update...
    if (isupper(m.p1)) { // Black piece
        blackkingpos[0] = m.x2;
        blackkingpos[1] = m.y2;
    } else { // White piece
        whitekingpos[0] = m.x2;
        whitekingpos[1] = m.y2;
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
//n is the same as the number of turns and its taken by reference to avoid logical errors when redoing again
/*void rumode(char **board,int *n){
    int start=*n;
    char op='/';
    while(op!='e'){ //i think we should not read input in here input should be handled in main
        scanf(" %c",&op);//space before %c to ignore whitespace characters
        switch (op)
        {
        case 'u' :
            if (*n==0) continue;
            undo(board,moves[*n-1]);//index was off by one i fixed it
            *n--;
            break;
        case 'r' :
             if (*n==start) continue;
            redo(board,moves[*n]);  //you seemed to forget that arrays start from 0 moves[0] is the first move so i fixed it
            *n++;
            break;
        
        default:
            printf("invalid input");
            continue;
            break;
        }
        boardprint(board);

    }
    //no need to clear the array bec it will do this by its own bec the n of the turns is decreased

}
*/