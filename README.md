

# Chess Game Implementation in C

**Authors:** John Bassem, Justin Jimmy
**Language:** C
**Paradigm:** Procedural Programming
**Platform:** Linux / GCC

---

## 1. Application Description and Features

### 1.1 Overview

This application is a **fully playable chess game implemented in the C programming language**, designed to run in a terminal environment. The program simulates a real chess match between two players, enforcing all standard chess rules and providing additional quality-of-life features such as saving/loading games and undo/redo functionality.

The game uses a **text-based board representation**, accepts algebraic-like move inputs (e.g., `e2e4`), and alternates turns automatically between White and Black.

---

### 1.2 Main Features

The application provides the following features:

#### Core Gameplay

* Complete chess rules enforcement:

  * Legal move validation for **all pieces**
  * **Check**, **checkmate**, and **stalemate** detection
* Turn-based play (White and Black)
* Board printed from the current player’s perspective

#### Advanced Chess Rules

* **Castling** (king-side and queen-side)

  * Correctly tracks castling rights
  * Prevents castling through check or when king/rook has moved
* **En Passant**

  * Tracks en passant target square
  * Correctly handles capture and undo/redo
* **Pawn Promotion**

  * User chooses promotion piece (`q`, `r`, `b`, `n`)

#### Game State Control

* **Undo** last move
* **Redo** undone moves
* **Save** game state to a binary file
* **Load** a previously saved game
* Keeps track of **captured (dead) pieces**

#### User Interface

* Clear prompts and instructions
* Error messages for invalid moves
* Displays captured pieces for both sides

---

## 2. Design Overview

### 2.1 Design Philosophy

The design emphasizes:

* **Modularity**
* **Separation of concerns**
* **Explicit state tracking**

Instead of relying on hidden state or implicit logic, all important aspects of the game (board, moves, king positions, castling rights, en passant target, captured pieces) are explicitly stored and updated.

---

### 2.2 Modular Structure

The program is divided into logical modules, each responsible for a specific aspect of the game:

| Module       | Responsibility                             |
| ------------ | ------------------------------------------ |
| `main.c`     | Game loop, user interaction, turn handling |
| `utility.c`  | Board creation, printing, checks, helpers  |
| `pieces.c`   | Piece-specific movement validation         |
| `rules.c`    | Game rules, checkmate/stalemate logic      |
| `undo.c`     | Move history, undo/redo system             |
| `saveload.c` | Binary save/load functionality             |

Each `.c` file has a corresponding `.h` file defining its interface.

---

## 3. Design and Implementation Assumptions

### 3.1 Board Representation

* The chessboard is stored as a **10×10 dynamically allocated array**

  * Indices `1..8` represent playable squares
  * Outer border used for labels (`a–h`, `1–8`)
* Empty squares are represented using:

  * `.` or `-` (to preserve checkerboard pattern)

### 3.2 Piece Representation

* **Lowercase letters** → White pieces
* **Uppercase letters** → Black pieces

| Piece  | White | Black |
| ------ | ----- | ----- |
| King   | `k`   | `K`   |
| Queen  | `q`   | `Q`   |
| Rook   | `r`   | `R`   |
| Bishop | `b`   | `B`   |
| Knight | `n`   | `N`   |
| Pawn   | `p`   | `P`   |

### 3.3 Input Format

* Moves must be entered in the format:

  ```
  e2e4
  ```
* Commands:

  * `undo`
  * `redo`
  * `save`
  * `exit`

Invalid input is rejected safely without crashing the program.

---

## 4. Data Structures Used

### 4.1 Board

```c
char **board;
```

* Dynamically allocated 2D array
* Stores pieces, empty squares, and board labels

---

### 4.2 Move Structure

```c
typedef struct {
    int x1, y1;
    char p1;
    int x2, y2;
    char p2;

    int rook_x1, rook_x2;
    char r_p1;

    char ep_captured_p;
    char promotion;

    int wkx_before, wky_before;
    int bkx_before, bky_before;

    int n;
} move;
```

This structure fully captures **everything required to undo and redo a move**, including:

* Captures
* Castling rook movement
* En passant
* Promotion
* King positions before the move

---

### 4.3 Move History

```c
move moves[1024];
```

* Acts as a **stack**
* Index `n` represents the current move number

---

### 4.4 Global State Variables

```c
int ep_target_x, ep_target_y;
bool wk_castle_ks, wk_castle_qs;
bool bk_castle_ks, bk_castle_qs;
int deadn;
```

These track:

* En passant square
* Castling rights
* Number of captured pieces

---

## 5. Important Functions and Modules

### 5.1 `main.c`

* Initializes the game
* Handles user input
* Controls turn order
* Calls move validation, execution, undo/redo
* Checks for game termination

---

### 5.2 `movevalidator()`

Validates a move by:

1. Checking piece movement rules
2. Simulating the move
3. Verifying the king is not left in check
4. Reverting the simulation
5. returning wether the move is valid or not

This ensures **no illegal move can be played**, even if it appears valid locally(ex.the king is in danger but there is nothing else the can stop the rook.

---

### 5.3 `inCheck()`

Determines whether a king is under attack by:

* Rooks / Queens (straight lines)
* Bishops / Queens (diagonals)
* Knights
* Pawns
* Opposing king

Highly optimized compared to brute-force checking.

---

### 5.4 `endgamecheck()`

Determines:

* Normal play
* Checkmate
* Stalemate

Logic:

* If any legal move exists → game continues
* it checks by checking every square for every piece and returns 0 if it found any possible move else returns 1 or 2
* If none exist:

  * King in check → Checkmate
  * King safe → Stalemate

---

### 5.5 Undo / Redo System

* **Undo:** Restores board, king positions, captures, castling, EP
* **Redo:** Reapplies move exactly as before

This is achieved by storing **complete move metadata**, not recomputing state.
every move is stored in a struct containing all flags, point 1 and 2 and promotion.
undo and redo work by moving through this stack of moves going back and forth

---

### 5.6 Save / Load

* Saves number of moves and move struct array to a **binary file**
* Reloading replays moves from the initial board
* Guarantees consistency without saving the board itself
* loading also reinnializes the flags from the last moves
* since its loaded from the move struct ,the user still has access to the redo and undo even after closing the game and loading

---

## 6. User Manual

### 6.1 Starting the Game

Run the program:

```bash
./chess
```

You will be prompted:

```
enter l to load game or anything else to start a new game
```

---

### 6.2 Making Moves

Enter moves in this format:

```
e2e4
```

---

### 6.3 Commands

| Command | Action                |
| ------- | --------------------- |
| `undo`  | Undo last move        |
| `redo`  | Redo last undone move |
| `save`  | Save game to file     |
| `exit`  | Exit the game         |

---

### 6.4 Promotion

When a pawn reaches the final rank:

```
Promote pawn to (q,r,b,n):
```

---

### 6.5 Game End

* Checkmate message is displayed
* Stalemate is declared correctly
* Program terminates gracefully

---
