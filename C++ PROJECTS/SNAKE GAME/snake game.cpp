/*
 * ========================================
 * CONSOLE SNAKE GAME
 * ========================================
 *
 * Author: GADZIDE Komi Joël
 * Date: November 2024
 * Language: C++
 *
 * Description:
 * A complete implementation of the classic Snake game with console graphics,
 * featuring smooth gameplay, score tracking, and increasing difficulty.
 *
 * Features:
 * - Real-time keyboard input handling
 * - Collision detection (walls, self-collision)
 * - Dynamic game board rendering
 * - Score system with high score tracking
 * - Increasing difficulty levels
 * - Food generation and consumption
 * - Game state management (pause, game over)
 *
 * Game Mechanics:
 * - Snake grows when eating food
 * - Game speed increases with score
 * - Responsive controls (WASD/Arrow keys)
 * - Boundary wrapping or wall collision options
 *
 * Concepts Demonstrated:
 * - Game loop architecture
 * - Console graphics and animation
 * - Input handling without external libraries
 * - Collision detection algorithms
 * - State machine implementation
 * - Object-oriented game design
 * ========================================
 */

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <random>
#include <algorithm>

using namespace std;

// ========================================
// CONSTANTS AND CONFIGURATION
// ========================================
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 15;
const int INITIAL_SNAKE_LENGTH = 3;
const int BASE_GAME_SPEED = 150; // milliseconds

// ========================================
// ENUMERATIONS AND STRUCTURES
// ========================================
enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };
enum class GameState { RUNNING, PAUSED, GAME_OVER, EXIT };

struct Position {
    int x, y;

    Position(int xPos = 0, int yPos = 0) : x(xPos), y(yPos) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

// ========================================
// SNAKE CLASS
// ========================================
class Snake {
private:
    vector<Position> body;
    Direction currentDirection;
    Direction nextDirection;
    bool growNextMove;

public:
    Snake() : growNextMove(false) {
        reset();
    }

    void reset() {
        body.clear();
        currentDirection = Direction::RIGHT;
        nextDirection = Direction::RIGHT;
        growNextMove = false;

        // Initialize snake in the middle of the board
        int startX = BOARD_WIDTH / 2;
        int startY = BOARD_HEIGHT / 2;

        for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
            body.push_back(Position(startX - i, startY));
        }
    }

    void setDirection(Direction newDirection) {
        // Prevent 180-degree turns
        if ((currentDirection == Direction::UP && newDirection != Direction::DOWN) ||
            (currentDirection == Direction::DOWN && newDirection != Direction::UP) ||
            (currentDirection == Direction::LEFT && newDirection != Direction::RIGHT) ||
            (currentDirection == Direction::RIGHT && newDirection != Direction::LEFT)) {
            nextDirection = newDirection;
        }
    }

    void move() {
        // Update direction
        currentDirection = nextDirection;

        // Calculate new head position
        Position newHead = body.front();

        switch (currentDirection) {
            case Direction::UP:    newHead.y--; break;
            case Direction::DOWN:  newHead.y++; break;
            case Direction::LEFT:  newHead.x--; break;
            case Direction::RIGHT: newHead.x++; break;
            case Direction::NONE:  break;
        }

        // Handle board wrapping
        if (newHead.x < 0) newHead.x = BOARD_WIDTH - 1;
        if (newHead.x >= BOARD_WIDTH) newHead.x = 0;
        if (newHead.y < 0) newHead.y = BOARD_HEIGHT - 1;
        if (newHead.y >= BOARD_HEIGHT) newHead.y = 0;

        // Add new head
        body.insert(body.begin(), newHead);

        // Remove tail if not growing
        if (!growNextMove) {
            body.pop_back();
        } else {
            growNextMove = false;
        }
    }

    void grow() {
        growNextMove = true;
    }

    bool checkSelfCollision() const {
        const Position& head = body.front();

        // Check if head collides with any body segment (excluding head itself)
        for (size_t i = 1; i < body.size(); i++) {
            if (head == body[i]) {
                return true;
            }
        }
        return false;
    }

    bool checkWallCollision() const {
        const Position& head = body.front();
        return (head.x < 0 || head.x >= BOARD_WIDTH ||
                head.y < 0 || head.y >= BOARD_HEIGHT);
    }

    const Position& getHead() const {
        return body.front();
    }

    const vector<Position>& getBody() const {
        return body;
    }

    int getLength() const {
        return body.size();
    }

    bool containsPosition(const Position& pos) const {
        for (const auto& segment : body) {
            if (segment == pos) {
                return true;
            }
        }
        return false;
    }
};

// ========================================
// FOOD CLASS
// ========================================
class Food {
private:
    Position position;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> distX;
    uniform_int_distribution<int> distY;

public:
    Food() : gen(rd()), distX(0, BOARD_WIDTH - 1), distY(0, BOARD_HEIGHT - 1) {
        respawn();
    }

    void respawn(const Snake& snake) {
        Position newPos;
        bool validPosition = false;

        // Keep generating until we find a position not occupied by the snake
        while (!validPosition) {
            newPos.x = distX(gen);
            newPos.y = distY(gen);
            validPosition = !snake.containsPosition(newPos);
        }

        position = newPos;
    }

    void respawn() {
        position.x = distX(gen);
        position.y = distY(gen);
    }

    const Position& getPosition() const {
        return position;
    }

    bool isEaten(const Snake& snake) const {
        return snake.getHead() == position;
    }
};

// ========================================
// GAME ENGINE CLASS
// ========================================
class SnakeGame {
private:
    Snake snake;
    Food food;
    GameState state;
    int score;
    int highScore;
    int gameSpeed;
    bool wallsEnabled;

    void setupConsole() {
        // Set console title
        SetConsoleTitleA("Snake Game - CSC Portfolio Project");

        // Hide cursor
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void restoreConsole() {
        // Show cursor
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void processInput() {
        if (_kbhit()) {
            int key = _getch();

            // Handle arrow keys (Windows)
            if (key == 224) {
                key = _getch();
                switch (key) {
                    case 72: snake.setDirection(Direction::UP); break;
                    case 80: snake.setDirection(Direction::DOWN); break;
                    case 75: snake.setDirection(Direction::LEFT); break;
                    case 77: snake.setDirection(Direction::RIGHT); break;
                }
            }
            // Handle WASD keys
            else {
                switch (key) {
                    case 'w': case 'W': snake.setDirection(Direction::UP); break;
                    case 's': case 'S': snake.setDirection(Direction::DOWN); break;
                    case 'a': case 'A': snake.setDirection(Direction::LEFT); break;
                    case 'd': case 'D': snake.setDirection(Direction::RIGHT); break;
                    case 'p': case 'P': togglePause(); break;
                    case 'r': case 'R': if (state == GameState::GAME_OVER) resetGame(); break;
                    case 27: state = GameState::EXIT; break; // ESC key
                }
            }
        }
    }

    void update() {
        snake.move();

        // Check for food consumption
        if (food.isEaten(snake)) {
            snake.grow();
            food.respawn(snake);
            score += 10;

            // Increase speed based on score
            gameSpeed = max(50, BASE_GAME_SPEED - (score / 50) * 10);

            // Update high score
            if (score > highScore) {
                highScore = score;
            }
        }

        // Check for collisions
        if (snake.checkSelfCollision() || (wallsEnabled && snake.checkWallCollision())) {
            state = GameState::GAME_OVER;
        }
    }

    void render() {
        system("cls"); // Clear console (Windows)

        // Draw top border
        cout << "  ";
        for (int x = 0; x < BOARD_WIDTH + 2; x++) {
            cout << (wallsEnabled ? "#" : "=");
        }
        cout << endl;

        // Draw game board
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            cout << "  " << (wallsEnabled ? "#" : "|"); // Left border

            for (int x = 0; x < BOARD_WIDTH; x++) {
                Position currentPos(x, y);

                if (snake.getHead() == currentPos) {
                    cout << "O"; // Snake head
                }
                else if (snake.containsPosition(currentPos)) {
                    cout << "o"; // Snake body
                }
                else if (food.getPosition() == currentPos) {
                    cout << "*"; // Food
                }
                else {
                    cout << " "; // Empty space
                }
            }

            cout << (wallsEnabled ? "#" : "|") << endl; // Right border
        }

        // Draw bottom border
        cout << "  ";
        for (int x = 0; x < BOARD_WIDTH + 2; x++) {
            cout << (wallsEnabled ? "#" : "=");
        }
        cout << endl;

        // Draw game information
        cout << "\n  SCORE: " << score << " | HIGH SCORE: " << highScore;
        cout << " | LENGTH: " << snake.getLength() << endl;

        // Draw game state message
        switch (state) {
            case GameState::PAUSED:
                cout << "  *** GAME PAUSED - Press P to resume ***" << endl;
                break;
            case GameState::GAME_OVER:
                cout << "  *** GAME OVER - Press R to restart or ESC to exit ***" << endl;
                break;
            case GameState::RUNNING:
                cout << "  Controls: WASD/Arrow Keys | P: Pause | ESC: Exit" << endl;
                break;
            default:
                break;
        }
    }

    void togglePause() {
        if (state == GameState::RUNNING) {
            state = GameState::PAUSED;
        } else if (state == GameState::PAUSED) {
            state = GameState::RUNNING;
        }
    }

    void resetGame() {
        snake.reset();
        food.respawn(snake);
        score = 0;
        gameSpeed = BASE_GAME_SPEED;
        state = GameState::RUNNING;
    }

public:
    SnakeGame() : state(GameState::RUNNING), score(0), highScore(0),
                  gameSpeed(BASE_GAME_SPEED), wallsEnabled(false) {
        setupConsole();
        resetGame();
    }

    ~SnakeGame() {
        restoreConsole();
    }

    void run() {
        cout << "========================================" << endl;
        cout << "        CONSOLE SNAKE GAME" << endl;
        cout << "    Author: GADZIDE Komi Joël" << endl;
        cout << "========================================\n" << endl;

        cout << "Starting game in 3 seconds..." << endl;
        this_thread::sleep_for(chrono::seconds(3));

        while (state != GameState::EXIT) {
            auto frameStart = chrono::high_resolution_clock::now();

            processInput();

            if (state == GameState::RUNNING) {
                update();
            }

            render();

            // Frame rate control
            auto frameEnd = chrono::high_resolution_clock::now();
            auto frameTime = chrono::duration_cast<chrono::milliseconds>(frameEnd - frameStart);
            auto sleepTime = gameSpeed - frameTime.count();

            if (sleepTime > 0) {
                this_thread::sleep_for(chrono::milliseconds(sleepTime));
            }
        }

        cout << "\nThank you for playing!" << endl;
    }

    // Configuration methods
    void enableWalls(bool enable) { wallsEnabled = enable; }
    void setGameSpeed(int speed) { gameSpeed = speed; }
};

// ========================================
// MAIN FUNCTION
// ========================================
int main() {
    try {
        SnakeGame game;

        // Configuration options
        game.enableWalls(false); // Set to true for wall collisions instead of wrapping

        game.run();

    } catch (const exception& e) {
        cerr << "Game error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

/*
 * ========================================
 * COMPILATION AND EXECUTION:
 * ========================================
 *
 * To compile (Windows with MinGW):
 *   g++ -std=c++17 snake_game.cpp -o snake_game
 *
 * To run:
 *   ./snake_game
 *
 * ========================================
 * CONTROLS:
 * ========================================
 *
 * - WASD or Arrow Keys: Move snake
 * - P: Pause/Resume game
 * - R: Restart game (after game over)
 * - ESC: Exit game
 *
 * ========================================
 * GAME FEATURES:
 * ========================================
 *
 * 1. GAMEPLAY MECHANICS:
 *    - Snake grows when eating food
 *    - Increasing difficulty with speed
 *    - Self-collision detection
 *    - Configurable wall behavior (wrap or collide)
 *
 * 2. USER INTERFACE:
 *    - Real-time score display
 *    - High score tracking
 *    - Visual game state indicators
 *    - Clean console-based graphics
 *
 * 3. TECHNICAL FEATURES:
 *    - Smooth game loop with frame rate control
 *    - Responsive keyboard input
 *    - Efficient collision detection
 *    - Object-oriented architecture
 *
 */

