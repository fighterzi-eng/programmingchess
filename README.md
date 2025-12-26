# Chess Game Implementation in C

**Authors:** John Bassem, Justin Jimmy

**Language:** C

**Paradigm:** Procedural Programming

**Platform:** Windows/ Linux / GCC

---

## 1. Application Description and Features

### 1.1 Overview

This application is a **fully playable chess game implemented in the C programming language**, designed for the terminal. It simulates a professional chess match by enforcing standard FIDE rules and provides a modern interface featuring move history navigation and binary state persistence.

The program supports **dynamic board rotation**, ensuring the board is always printed from the perspective of the current player (White or Black).

---

### 1.2 Main Features

#### Core Gameplay

* **Complete Rule Enforcement**: Validates movement for all pieces including specialized logic for King safety.
* **Game State Detection**: Automatic detection of **Check**, **Checkmate**, and **Stalemate**.
* **Dynamic Perspective**: The board flips automatically based on whose turn it is.

#### Advanced Chess Rules

* **Castling**: Handles King-side and rook-side logic, verifying that the path is clear and no pieces are under attack.
* **En Passant**: Tracks the double-pawn-push target square and handles the unique capture logic.
* **Pawn Promotion**: Interactive selection of Queen, Rook, Bishop, or Knight when a pawn reaches the 8th rank.

#### Game State Control

* **Undo/Redo System**: A full stack-based system to navigate back and forth through the match.
* **Binary Save/Load**: Allows players to save their progress to a `.bin` file and resume later with the full undo history intact.
* **multiple save files**: the user has the option to save and load from multiple files
* **Captured Material**: Visual tracking of "dead" pieces for both players.

#### User Interface
the user interface is very user friendly ensuring that the normal user never gets lost

* **Graphics Toggle**: Support for both **Unicode Fancy Graphics** (♔, ♞) and standard **ASCII** (k, n).
* **Input Handling**: Robust parsing of algebraic notation (e.g., `e2e4`) and command strings.

---

## 2. Design Overview

### 2.1 Design Philosophy

The architecture emphasizes **History-Based State**. Instead of storing only the current board, the system records a sequence of transformations. This ensures that the state can be perfectly reconstructed or reverted without loss of data or "ghost" logic errors.

---

### 2.2 Modular Structure

| Module | Responsibility |
| --- | --- |
| `main.c` | Entry point, game loop, menu management, and turn-based logic. |
| `utility.c` | Board initialization, coordinate mapping, and perspective-aware printing. |
| `pieces.c` | Specific legal movement patterns for each unique chess piece. |
| `rules.c` | High-level validation (Check/Checkmate), move simulation, and capture logic. |
| `undo.c` | Stack management for move history and state restoration. |
| `saveload.c` | Binary File I/O for persistent storage of the move history. |

---

## 3. Design and Implementation Assumptions

### 3.1 Board Representation

* The board is a **10x10 dynamically allocated array**.(helps with wider access to the board)
* Indices `1..8` are the active squares.
* Outer indices provide coordinate labels (`a-h`, `1-8`).


* Empty squares use `.` and `-` to maintain a visual checkerboard pattern in the terminal.

### 3.2 Piece Representation

* **Lowercase** = White pieces | **Uppercase** = Black pieces.
* Supports Unicode characters if the terminal and user settings allow.

### 3.3 Input Format

* **Moves**: Entered as source-destination pairs (e.g., `g1f3`).
* **Menu**: Users select from `Start`, `Load`, or `Exit` at the beginning of the program,those options also can be selected at any time

---

## 4. Data Structures Used

### 4.1 Move Structure

```c
typedef struct {
    int x1, y1, x2, y2;
    char p1, p2;           // Source piece and destination (capture)
    int rook_x1, rook_x2;  // For castling rook movement
    char r_p1;             // Rook piece type
    char ep_captured_p;    // En Passant target piece
    char promotion;        // Promotion piece selection
    int wkx_before, wky_before, bkx_before, bky_before; // King positions
    bool wk_ks, wk_qs, bk_ks, bk_qs; // Castling rights snapshot
    int ep_tx, ep_ty;      // En Passant target square snapshot
    int n;                 // Move sequence number
} move;

```

---

### 4.2 Global State Variables

* `move moves[1024]`: The stack containing every move played in the session.
* `char dead[32]`: A buffer storing all captured pieces.
* `bool use_fancy_graphics`: Toggle for Unicode vs ASCII output.

---

## 5. Important Functions and Modules

### 5.1 `movevalidator()`

This is the core engine function. It works in two phases:

1. **Geometric Check**: Calls functions in `pieces.c` to see if the move follows piece rules.
2. **King Safety**: Simulates the move on the board and calls `inCheck()`. If the player's king is left in danger, the move is invalidated and the board is reverted.
3. the casteling and en passant are checked by global variable that indicates wether there still a possibility for this move or not.

### 5.2 `inCheck()`

Determines if a king is under attack. It is optimized to scan outwards from the king’s current coordinate in rays (for Sliders) and specific offsets (for Knights/Pawns) to identify threats.

### 5.3 `endgamecheck()`

Determines the status of the game:

* **0**: Play continues.
* **1**: Checkmate (King is in check and no legal moves exist).
* **2**: Stalemate (King is safe but no legal moves exist).

### 5.4 `Save / Load ( )`

The system saves the entire `moves` array and the move count `n`. When loading, the program initializes a fresh board and **replays** the history. This ensures the player can still `undo` moves that occurred before the game was saved.


### 5.3 `addmove()`
this function despite its simplicity plays a very crucial rule in the undo/redo logic it adds all the move details to the moves array


---

## 6. User Manual

### 6.1 Starting the Game

1. Run `./bin/chess`.
2. Select graphics mode: `y` for Unicode (Fancy), `n` for ASCII.
3. Choose `Start` for a new game or `Load` to open a `.bin` file.

### 6.2  Gameplay Commands

| Command | Result |
| --- | --- |
| `e2e4` | Standard move input. |
| `undo` | Reverts the last move. |
| `redo` | Restores a previously undone move. |
| `save` | Prompts for a filename to save the binary state. |
| `load` | Prompts for a filename to load the binary state. |
| `exit` | Terminates the program. |

### 6.3 Special Rules Handling

 1. **Promotion**: When a pawn reaches the opposite end, the user is prompted to enter `q`, `r`, `b`, or `n`.
 2. **Castling**: Input the king's move (e.g., `e1g1`); the rook will move automatically,same goes for the en passant
 3. **Dead Pieces**: All captured material is displayed below the board after every turn.
---
## 7 Test cases:
 ohn@john-ASUS-TUF-Gaming-F15-FX507ZC4-FX507ZC4:~/progproject/programmingchess$ ./bin/chess
Welcome to our Chess Game!
Enable ASCII graphics? (y/n): y
---------------Menu---------------
               Start               
               Load                
               exit                
----------------------------------
start

    A B C D E F G H
  +-----------------+
8 | ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ | 8
7 | ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ | 7
6 | ■ □ ■ □ ■ □ ■ □ | 6
5 | □ ■ □ ■ □ ■ □ ■ | 5
4 | ■ □ ■ □ ■ □ ■ □ | 4
3 | □ ■ □ ■ □ ■ □ ■ | 3
2 | ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ | 1
  +-----------------+
    A B C D E F G H


Enter your move in format ex: (e2e4):
Enter 'undo' to undo last move or 'redo' to redo last undone move you can also write'save' to save
White to move
Enter your move: e2e4

    A B C D E F G H
  +-----------------+
1 | ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ | 1
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
3 | □ ■ □ ■ □ ■ □ ■ | 3
4 | ■ □ ■ □ ♟ □ ■ □ | 4
5 | □ ■ □ ■ □ ■ □ ■ | 5
6 | ■ □ ■ □ ■ □ ■ □ | 6
7 | ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ | 7
8 | ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: e7e5

    A B C D E F G H
  +-----------------+
8 | ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ | 8
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
6 | ■ □ ■ □ ■ □ ■ □ | 6
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
4 | ■ □ ■ □ ♟ □ ■ □ | 4
3 | □ ■ □ ■ □ ■ □ ■ | 3
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: g1f3

    A B C D E F G H
  +-----------------+
1 | ♜ ♞ ♝ ♛ ♚ ♝ □ ♜ | 1
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
3 | □ ■ □ ■ □ ♞ □ ■ | 3
4 | ■ □ ■ □ ♟ □ ■ □ | 4
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ □ ■ □ ■ □ | 6
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
8 | ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: b8c6

    A B C D E F G H
  +-----------------+
8 | ♖ □ ♗ ♕ ♔ ♗ ♘ ♖ | 8
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ □ ■ □ ■ □ | 6
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
4 | ■ □ ■ □ ♟ □ ■ □ | 4
3 | □ ■ □ ■ □ ♞ □ ■ | 3
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ♝ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: f1c4

    A B C D E F G H
  +-----------------+
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
3 | □ ■ □ ■ □ ♞ □ ■ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ □ ■ □ ■ □ | 6
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
8 | ♖ □ ♗ ♕ ♔ ♗ ♘ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: g8f6

    A B C D E F G H
  +-----------------+
8 | ♖ □ ♗ ♕ ♔ ♗ ■ ♖ | 8
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ □ ■ ♘ ■ □ | 6
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ □ ■ □ ♞ □ ■ | 3
2 | ♟ ♟ ♟ ♟ ■ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: d2d3

    A B C D E F G H
  +-----------------+
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ ♟ ♟ □ ■ ♟ ♟ ♟ | 2
3 | □ ■ □ ♟ □ ♞ □ ■ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ □ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ □ ■ ♘ ■ □ | 6
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
8 | ♖ □ ♗ ♕ ♔ ♗ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: f8c5

    A B C D E F G H
  +-----------------+
8 | ♖ □ ♗ ♕ ♔ □ ■ ♖ | 8
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ □ ■ ♘ ■ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ □ ♟ □ ♞ □ ■ | 3
2 | ♟ ♟ ♟ □ ■ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: c2c3

    A B C D E F G H
  +-----------------+
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ ♟ ■ □ ■ ♟ ♟ ♟ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ■ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ □ ■ ♘ ■ □ | 6
7 | ♙ ♙ ♙ ♙ □ ♙ ♙ ♙ | 7
8 | ♖ □ ♗ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: d7d6

    A B C D E F G H
  +-----------------+
8 | ♖ □ ♗ ♕ ♔ □ ■ ♖ | 8
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ■ | 3
2 | ♟ ♟ ■ □ ■ ♟ ♟ ♟ | 2
1 | ♜ ♞ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: b1d2

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ ♟ ■ ♞ ■ ♟ ♟ ♟ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ■ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ♗ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: c8g4

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ♗ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ■ | 3
2 | ♟ ♟ ■ ♞ ■ ♟ ♟ ♟ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: h2h3

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ ♟ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ♗ □ | 4
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: g4h5

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ♗ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ♟ ♟ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: b2b4

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ♟ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ ♟ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ ♗ ■ ♙ ■ □ ♗ | 5
6 | ■ □ ♘ ♙ ■ ♘ ■ □ | 6
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: h5g6

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ ♙ ■ ♘ ♗ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ ♟ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ♟ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: a2a4

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
4 | ♟ ♟ ♝ □ ♟ □ ■ □ | 4
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ ♙ ■ ♘ ♗ □ | 6
7 | ♙ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: a7a6

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ♙ □ ♘ ♙ ■ ♘ ♗ □ | 6
5 | □ ■ ♗ ■ ♙ ■ □ ■ | 5
4 | ♟ ♟ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
White to move
Enter your move: b4b5

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
4 | ♟ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ♙ □ ♘ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: (none)   Black: (none)
Black to move
Enter your move: a6b5

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
6 | ■ □ ♘ ♙ ■ ♘ ♗ □ | 6
5 | □ ♙ ♗ ■ ♙ ■ □ ■ | 5
4 | ♟ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: (none)
White to move
Enter your move: a4b5

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ♘ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ■ □ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: ♙ 
Black to move
Enter your move: c6e7

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ■ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: ♙ 
White to move
Enter your move: d1b3

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ■ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: ♙ 
Black to move
Enter your move: d8d7

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: ♙ 
White to move
Enter your move: redo
Nothing to redo!
White to move
Enter your move: undo

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ■ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Black to move
Enter your move: undo

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ■ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ■ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ♛ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

White to move
Enter your move: redo

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ■ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ ♕ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Black to move
Enter your move: redo

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

White to move
Enter your move: save
Enter filename to save example: savefile.bin savesave.bin
White to move
Enter your move: exit

Made by: John Bassem and Justin Jimmy 
Thank you for playing!
john@john-ASUS-TUF-Gaming-F15-FX507ZC4-FX507ZC4:~/progproject/programmingchess$ ./bin/chess
Welcome to our Chess Game!
Enable ASCII graphics? (y/n): y
---------------Menu---------------
               Start               
               Load                
               Exit                
----------------------------------
load
Enter filename to load: savesave.bin

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H


    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H


Enter your move in format ex: (e2e4):
Enter 'undo' to undo last move or 'redo' to redo last undone move you can also write'save' to save
White to move
Enter your move: Bad move format
White to move
Enter your move: a1a3

    A B C D E F G H
  +-----------------+
1 | □ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | ♜ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Dead pieces  White: ♟    Black: ♙ 
Black to move
Enter your move: undo

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

White to move
Enter your move: undo

    A B C D E F G H
  +-----------------+
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Black to move
Enter your move: redo

    A B C D E F G H
  +-----------------+
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
3 | □ ♛ ♟ ♟ □ ♞ □ ♟ | 3
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
1 | ♜ ■ ♝ ■ ♚ ■ □ ♜ | 1
  +-----------------+
    A B C D E F G H

White to move
Enter your move: redo

    A B C D E F G H
  +-----------------+
1 | □ ■ ♝ ■ ♚ ■ □ ♜ | 1
2 | ■ □ ■ ♞ ■ ♟ ♟ □ | 2
3 | ♜ ♛ ♟ ♟ □ ♞ □ ♟ | 3
4 | ■ □ ♝ □ ♟ □ ■ □ | 4
5 | □ ♟ ♗ ■ ♙ ■ □ ■ | 5
6 | ■ □ ■ ♙ ■ ♘ ♗ □ | 6
7 | □ ♙ ♙ ♕ ♘ ♙ ♙ ♙ | 7
8 | ♖ □ ■ □ ♔ □ ■ ♖ | 8
  +-----------------+
    A B C D E F G H

Black to move
Enter your move: 

    

