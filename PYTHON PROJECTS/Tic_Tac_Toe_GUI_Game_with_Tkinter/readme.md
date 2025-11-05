##  Tic-Tac-Toe: Player vs. Computer (AI with Variable Difficulty)

This project features the classic Tic-Tac-Toe game, implemented with Tkinter, showcasing a structured approach to **Game AI** and **Modularity** by introducing a configurable difficulty level.

### Key Features for the Jury

1.  **Variable Difficulty:** The core feature is the ability to modulate the computer's performance using the global `DIFFICULTY_LEVEL`:
    * **HARD:** Near-perfect play (5% chance of error).
    * **MEDIUM (Default):** Strategic play with occasional, human-like mistakes (30% chance of error).
    * **EASY:** High probability of random, non-strategic moves (70% chance of error).
2.  **Hybrid AI Strategy:** The computer's decision-making process prioritizes key strategic moves (Win > Block > Center/Corners) but is subject to an initial **random chance of error** based on the chosen difficulty.
3.  **Demonstrates Modularity:** The code clearly separates the game logic (Win/Draw checks) from the AI decision logic, making the code flexible and scalable.

### AI Decision Flow

The `computer_move` function executes the following steps:

1.  **Chance Roll:** Checks if a random number falls below the `DIFFICULTY_CHANCE` threshold. If so, a purely random move is executed (the mistake).
2.  **Win Check:** If no mistake, check for an immediate winning move for 'O'.
3.  **Block Check:** If no win, check for an immediate winning move for 'X' and block it.
4.  **Heuristic:** If no immediate threat, choose the best cell based on priority (Center > Corners > Sides).
