# Endless Car Runner Game (Pygame)

## Technical Highlights

This project serves as a practical demonstration of core software architecture and game development principles using **Python** and **Pygame**:

1.  **Object-Oriented Design (OOP):** Effective use of **Sprite Inheritance** (`Vehicle`, `PlayerVehicle`) for modular asset management and collision handling.
2.  **Scrolling Algorithm:** Implements an **Endless Scrolling** effect for the road, demonstrating coordinate manipulation to create a seamless illusion of motion.
3.  **Advanced Logic:**
    * **Dynamic Difficulty:** Progressive **scaling** of game speed based on the score.
    * **Robust Collision:** Logic distinguishes between head-on and **side-swipe** collisions for complete interaction handling.
4.  **State Management:** Clear separation between the main game loop and a dedicated **pause loop** (`while gameover`), ensuring clean state transitions.

## 🛠️ Setup & Controls

| Element | Detail |
| :--- | :--- |
| **Technology** | Python 3.x, **Pygame** |
| **Prerequisite** | `pip install pygame` |
| **Assets** | Image files (e.g., `car.png`, `taxi.png`) must be in the **same directory** as the script. |
| **Controls** | **Left/Right Arrows** (Steer), **Y** (Replay), **N** (Quit) |