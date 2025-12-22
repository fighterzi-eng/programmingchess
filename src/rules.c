#include"include/rules.h"
#include"include/undo.h"
#include"include/utility.h"

int endgamecheck(int*kingpos,char**board){
  int kx=kingpos[0];
  int ky=kingpos[1];
  for (int i=1;i<9;i++){
    for (int j=1;j<9;j++){
      if (EMPTY(board[i][j])) continue;
      if (isupper(board[i][j])!=isupper(board[ky][kx])) continue;
      else{
         for (int k=1;k<9;k++){
    for (int p=1;p<9;p++){
      if (movevalidator(j,i,k,p,board,kingpos)==0) return 0;
    }}

      }
    
  }

  }
  if (inCheck(kx,ky,board)==1) return 1;//means checkmate
  else return 2;//means stale mate
}

int deadn = 0;          /* no longer static – we want to read it */
int char_cmp(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}
/*-----------  print dead material  -----------*/
void print_dead(const char *dead)
{
    int wn = 0, bn = 0;
    char white[32] = {0}, black[32] = {0};

    for (int i = 1; i <= deadn; ++i) {
        char p = dead[i];
        if (islower(p))            /* white piece died – impossible but keep */
            white[wn++] = (char)toupper(p);
        else                       /* black piece died */
            black[bn++] = p;
    }

qsort(white, wn, sizeof(char), char_cmp);
qsort(black, bn, sizeof(char), char_cmp);

    printf("Dead pieces  White: ");
    if (wn) printf("%.*s", wn, white);
    else    printf("(none)");

    printf("   Black: ");
    if (bn) printf("%.*s", bn, black);
    else    printf("(none)");
    puts("");
}
int movevalidator(int x1,int y1,int x2,int y2,char**board,int*kingpos){
  char piece=board[y1][x1];
  piece=toupper(piece);
  int validity=0;
  int kx=kingpos[0];
  int ky=kingpos[1];
  switch (piece)
  {
  case 'K':
    validity= king(x1,y1,x2,y2,board);
    if(validity==0){
      kx=x2;
      ky=y2;
    }
   
    break;
  case 'P':
    validity= pawn(x1,y1,x2,y2,board);
    break;
  case 'R':
    validity= rook(x1,y1,x2,y2,board);
    break;
  case 'N':
    validity= knight(x1,y1,x2,y2,board);
    break;
  case 'B':
    validity= bishop(x1,y1,x2,y2,board);
    break;
  case 'Q':
    if(bishop(x1,y1,x2,y2,board)==0||rook(x1,y1,x2,y2,board)==0) validity= 0;
    else validity= 1;
    break;
  
  default:
    printf("invalid piece");
    validity= 1;
    break;
  }
  
  //this part check if the king is in danger after the move ,i took abit from your king function underneath
  if (validity==0){
// Post-pattern validation: sim move & check king safety
if (validity == 0) {
    char savedFrom = board[y1][x1];
    char savedTo = board[y2][x2];

    // Update king pos for KING moves (before sim)
    int check_kx = kx;
    int check_ky = ky;
    if (piece == 'K') {
        check_kx = x2;
        check_ky = y2;
    }

    // Sim move
    board[y2][x2] = savedFrom;
    board[y1][x1] = '.';

    // EP sim: remove captured pawn if applicable
    char saved_cap = ' ';
    bool doing_ep = (abs(x2 - x1) == 1 && EMPTY(savedTo) && tolower(savedFrom) == 'p' &&
                     ((islower(savedFrom) && board[y1][x2] == 'P') ||
                      (isupper(savedFrom) && board[y1][x2] == 'p')));
    if (doing_ep) {
        saved_cap = board[y1][x2];
        board[y1][x2] = '.';
    }

    int illegal = inCheck(check_kx, check_ky, board);

    // Undo sim
    board[y1][x1] = savedFrom;
    board[y2][x2] = savedTo;
    if (doing_ep) {
        board[y1][x2] = saved_cap;
    }

    if (illegal) {
        validity = 1;  // Invalid: leaves king in check
    }
}

return validity;
  }
  return validity;
}
char check_promotion(char piece, int y2) {
    if ((piece == 'p' && y2 == 1) || (piece == 'P' && y2 == 8)) {
        char new_piece;
        printf("Promote pawn to (q,r,b,n): ");
        scanf(" %c", &new_piece);
        if (piece == 'P') new_piece = toupper(new_piece);
        return new_piece;
    }
    return '0';
}
void moving(move *m, char **board, char *dead) {
   
    m->p2 = board[m->y2][m->x2];  // Save to sq (empty for ep/castle)

    // CASTLE? (Detect and slide rook—flags not touched yet!)
    if (tolower(m->p1) == 'k' && abs(m->x2 - m->x1) == 2 && m->x1 == 5) {
        bool ks = (m->x2 > m->x1);
        m->rook_x1 = ks ? 8 : 1;
        m->rook_x2 = ks ? 6 : 4;
        m->r_p1 = board[m->y1][m->rook_x1];
        // Move rook
        char empty_r1 = ((m->y1 + m->rook_x1) % 2 == 0) ? '-' : '.';
        board[m->y1][m->rook_x2] = m->r_p1;
        board[m->y1][m->rook_x1] = empty_r1;
    }

    // EN PASSANT capture?
    bool is_ep = (tolower(m->p1) == 'p' && abs(m->x2 - m->x1) == 1 && 
                  EMPTY(m->p2) && board[m->y1][m->x2] == (islower(m->p1) ? 'P' : 'p'));
    if (is_ep) {
        m->ep_captured_p = board[m->y1][m->x2];
        char empty_cap = ((m->y1 + m->x2) % 2 == 0) ? '-' : '.';
        board[m->y1][m->x2] = empty_cap;
        // Dead: treat as capture
        deadn++; dead[deadn] = m->ep_captured_p;  // Adjust your deadn++ logic
    } else if (!EMPTY(m->p2)) {
        deadn++; dead[deadn] = m->p2;  // Normal capture
    }

    // Normal piece move (promotion handled)
    char ch = m->p1;
    if (m->promotion != '0') ch = m->promotion;
    board[m->y2][m->x2] = ch;
    board[m->y1][m->x1] = ((m->y1 + m->x1) % 2 == 0) ? '-' : '.';

    // SET EP TARGET (reset unless double pawn)
    if (tolower(m->p1) == 'p' && m->x1 == m->x2 && abs(m->y2 - m->y1) == 2 &&
        ((m->y1 == 7 && islower(m->p1)) || (m->y1 == 2 && isupper(m->p1)))) {
        ep_target_x = m->x2;
        ep_target_y = (m->y1 + m->y2) / 2;
    } else {
        ep_target_x = 0;
        ep_target_y = 0;
    }

    // NOW: Update castling flags! (After move committed—king/rook "has moved" now 😂)
    // Kill on KING move (both sides)
    if (tolower(m->p1) == 'k') {
        if (islower(m->p1)) {  // White
            wk_castle_ks = wk_castle_qs = false;
        } else {  // Black
            bk_castle_ks = bk_castle_qs = false;
        }
    }

    // Kill on ROOK move (check which one)
    else if (toupper(m->p1) == 'R') {  // Rook!
        int rx = m->x1;  // Orig pos
        bool is_white = islower(m->p1);
        if (is_white && m->y1 == 8) {  // White back rank
            if (rx == 1) wk_castle_qs = false;
            if (rx == 8) wk_castle_ks = false;
        } else if (m->y1 == 1) {  // Black
            if (rx == 1) bk_castle_qs = false;
            if (rx == 8) bk_castle_ks = false;
        }
    }
}