"""
Project: Tic-Tac-Toe - Human vs AI (Tkinter GUI)
Author: [Your Name/Group Name]
Date: November 2025
Description: A classic 3x3 Tic-Tac-Toe game implemented with Python's Tkinter.
             Features a human player (X) against an adjustable AI opponent (O).
             The AI's performance is governed by a global DIFFICULTY_LEVEL variable,
             introducing controlled randomness to simulate human-like mistakes.
"""

import tkinter
from tkinter import messagebox
import random

# ==============================================================================
#  1. GLOBAL CONFIGURATION & STATE MANAGEMENT
# ==============================================================================

# Constants for Difficulty (Probability of the AI making a non-optimal, random move)
DIFFICULTY_LEVEL = 'MEDIUM'
DIFFICULTY_CHANCE = {'EASY': 0.7, 'MEDIUM': 0.3, 'HARD': 0.05}

# Game state variables initialized
buttons = []            # 2D list to store references to the 9 Tkinter buttons
CURRENT_PLAYER = 'X'    # 'X' (Human) always starts first
GAME_OVER = False       # Flag to stop interaction when the game ends
AI_DELAY_MS = 500       # Time delay for the AI move (to make it noticeable)

# ==============================================================================
#  2. AI DECISION LOGIC (The core of the project)
# ==============================================================================

def get_empty_cells():
    """Helper: Returns a list of (row, col) coordinates for all available moves."""
    empty_cells = []
    for r in range(3):
        for c in range(3):
            if buttons[r][c]['text'] == "":
                empty_cells.append((r, c))
    return empty_cells

def check_lines_and_return_move(player):
    """
    Core AI logic: Checks the board for immediate win opportunities for 'player'
    (or blocking opportunities if 'player' is the opponent).
    Returns (row, col) of the necessary move, or None.
    """
    # 1. Check Rows
    for r in range(3):
        symbols = [buttons[r][c]['text'] for c in range(3)]
        if symbols.count(player) == 2 and symbols.count("") == 1:
            c = symbols.index("")
            return r, c

    # 2. Check Columns
    for c in range(3):
        symbols = [buttons[r][c]['text'] for r in range(3)]
        if symbols.count(player) == 2 and symbols.count("") == 1:
            r = symbols.index("")
            return r, c

    # 3. Check Main Diagonal (Top-Left to Bottom-Right)
    diag1_symbols = [buttons[i][i]['text'] for i in range(3)]
    if diag1_symbols.count(player) == 2 and diag1_symbols.count("") == 1:
        i = diag1_symbols.index("")
        return i, i

    # 4. Check Anti-Diagonal (Top-Right to Bottom-Left)
    diag2_symbols = [buttons[i][2-i]['text'] for i in range(3)]
    if diag2_symbols.count(player) == 2 and diag2_symbols.count("") == 1:
        i = diag2_symbols.index("")
        return i, 2-i

    return None

def computer_move():
    """Manages the AI's turn, including the strategic choice and the difficulty error."""
    global GAME_OVER

    if GAME_OVER:
        return

    # We introduce a delay here to simulate the AI 'thinking' and make its move visible.
    root.after(AI_DELAY_MS, execute_computer_move)

def execute_computer_move():
    """Applies the AI logic (Mistake factor, Win/Block checks, Heuristic)."""

    empty_cells = get_empty_cells()
    if not empty_cells:
        return # Should be caught by check_draw, but it's safer here.

    # --- Step 1: Human/Mistake Factor based on DIFFICULTY ---
    mistake_chance = DIFFICULTY_CHANCE[DIFFICULTY_LEVEL]

    if random.random() < mistake_chance:
        # The AI 'chose' to make a mistake (purely random move)
        r, c = random.choice(empty_cells)
        place_symbol(r, c)
        print(f"[AI Trace] Move was random ({DIFFICULTY_LEVEL} mistake chance: {mistake_chance*100:.0f}%)")
        return

    # --- Step 2: Optimal Strategy (Priorities) ---

    # 2a. Critical Priority: Check for immediate winning move (O wins)
    win_move = check_lines_and_return_move('O')
    if win_move:
        r, c = win_move
        place_symbol(r, c)
        return

    # 2b. Second Priority: Check for immediate blocking move (Block X)
    block_move = check_lines_and_return_move('X')
    if block_move:
        r, c = block_move
        place_symbol(r, c)
        return

    # 2c. Heuristic Priority: Choose the best available cell
    # The heuristic prioritizes the center, then corners, then sides.
    priority_moves = [
        (1, 1),         # Center is strategically most valuable
        (0, 0), (0, 2), (2, 0), (2, 2), # Corners are next best
        (0, 1), (1, 0), (1, 2), (2, 1)  # Sides are least valuable
    ]

    for r, c in priority_moves:
        if (r, c) in empty_cells:
            place_symbol(r, c)
            return

# ==============================================================================
#  3. GAME STATE AND LOGIC
# ==============================================================================

def switch_player():
    """Switches the turn and handles the transfer of control to the AI."""
    global CURRENT_PLAYER
    if CURRENT_PLAYER == 'X':
        CURRENT_PLAYER = 'O'
        status_label.config(text="Computer (O)'s turn")
        computer_move() # Give control to the AI
    else:
        CURRENT_PLAYER = 'X'
        status_label.config(text="Your (X)'s turn")

def check_win(clicked_row, clicked_col):
    """Checks if the last move completed a horizontal, vertical, or diagonal line."""
    # Check horizontal win (same row)
    if all(buttons[clicked_row][col]['text'] == CURRENT_PLAYER for col in range(3)): return True
    # Check vertical win (same column)
    if all(buttons[row][clicked_col]['text'] == CURRENT_PLAYER for row in range(3)): return True
    # Check main diagonal win
    if clicked_row == clicked_col and all(buttons[i][i]['text'] == CURRENT_PLAYER for i in range(3)): return True
    # Check anti-diagonal win
    if clicked_row + clicked_col == 2 and all(buttons[i][2 - i]['text'] == CURRENT_PLAYER for i in range(3)): return True
    return False

def check_draw():
    """Checks if all cells are filled (game is a draw)."""
    # Use 'any' to quickly exit if even one empty cell is found
    return not any(buttons[r][c]['text'] == "" for r in range(3) for c in range(3))

def end_game(message):
    """Stops the game, updates status, disables buttons, and prompts for restart."""
    global GAME_OVER
    GAME_OVER = True
    status_label.config(text=message)

    # Disable all buttons to freeze the board
    for row in range(3):
        for col in range(3):
            buttons[row][col].config(state='disabled')

    # --- MODIFICATION: Quitter si l'utilisateur refuse de rejouer ---
    if messagebox.askyesno("Game Over", f"{message}\n\nPlay again?"):
        reset_game()
    else:
        # Ferme la fenêtre et termine le programme
        root.destroy()
    # --- FIN DE MODIFICATION ---

def place_symbol(row, column):
    """Places the symbol, checks for win/draw, and passes the turn."""
    if GAME_OVER or buttons[row][column]["text"] != "":
        return # Ignore move if game over or cell occupied

    # 1. Execute Move
    buttons[row][column].config(text=CURRENT_PLAYER, fg='blue' if CURRENT_PLAYER == 'X' else 'red')

    # 2. Check Conditions
    if check_win(row, column):
        end_game(f"Player {CURRENT_PLAYER} wins!")
        return
    if check_draw():
        end_game("It's a draw!")
        return

    # 3. Next Turn
    switch_player()

def reset_game():
    """Initializes the board and state for a fresh game."""
    global GAME_OVER, CURRENT_PLAYER
    GAME_OVER = False
    CURRENT_PLAYER = 'X'

    for row in range(3):
        for col in range(3):
            buttons[row][col].config(text="", state='normal') # Clear and re-enable

    status_label.config(text="Your (X)'s turn")

# ==============================================================================
#  4. GUI SETUP (TKINTER)
# ==============================================================================

def draw_grid():
    """Creates the 3x3 grid of interactive buttons."""
    for row in range(3):
        button_row = []
        for column in range(3):
            button = tkinter.Button(
                root,
                font=("Arial", 50),
                width=5,
                height=2,
                # Command is protected to only execute if it's the Human's turn ('X')
                command=lambda r=row, c=column: place_symbol(r, c) if CURRENT_PLAYER == 'X' and not GAME_OVER else None,
                bg='lightgray'
            )
            # Use grid layout; row+1 leaves space for the status bar at row 0
            button.grid(row=row + 1, column=column, padx=2, pady=2)
            button_row.append(button)
        buttons.append(button_row)


# --- MAIN APPLICATION WINDOW ---
root = tkinter.Tk()
root.title(f"Tic Tac Toe - P vs AI (Difficulty: {DIFFICULTY_LEVEL})")
root.minsize(500, 550)
root.resizable(False, False)

# Status Label (Row 0)
status_label = tkinter.Label(root, text="Your (X)'s turn",
                             font=("Arial", 16), pady=10)
status_label.grid(row=0, column=0, columnspan=3)

# Draw the game grid (Rows 1-3)
draw_grid()

# Reset Button (Row 4)
reset_button = tkinter.Button(root, text="Reset Game", font=("Arial", 14),
                              command=reset_game, bg='lightblue')
reset_button.grid(row=4, column=0, columnspan=3, pady=10)

# Start the GUI event loop
root.mainloop()