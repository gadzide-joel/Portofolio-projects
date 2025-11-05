# --------------------------------------------------------------------------------------
# Project: Endless Car Runner Game - Pygame
# Author: [Your Name/Group Name]
# Date: November 2025
# Objectives: Demonstrates core game programming principles: OOP, sprite management, 
#             collision detection, and responsive background animation (scrolling).
# --------------------------------------------------------------------------------------

import pygame
from pygame.locals import *
import random
import sys # Added for cleaner exit

# Initialize Pygame
pygame.init()

# ==============================================================================
#  1. GLOBAL CONFIGURATION & CONSTANTS
# ==============================================================================

# --- Window Setup ---
SCREEN_WIDTH = 500
SCREEN_HEIGHT = 500
SCREEN_SIZE = (SCREEN_WIDTH, SCREEN_HEIGHT)
screen = pygame.display.set_mode(SCREEN_SIZE)
pygame.display.set_caption('Car Runner Game')

# --- Color Definitions (RGB) ---
GRAY = (100, 100, 100)      # Road color
GREEN = (76, 208, 56)       # Grass/background color
RED = (200, 0, 0)           # Color for the 'Game Over' display
WHITE = (255, 255, 255)     # Lane markings and text color
YELLOW = (255, 232, 0)      # Road edge line color

# --- Road and Lane Configuration ---
ROAD_WIDTH = 300
MARKER_WIDTH = 10
MARKER_HEIGHT = 50
PLAYER_START_X = 250
PLAYER_START_Y = 400

# X coordinates for the center of each lane
LEFT_LANE_X = 150
CENTER_LANE_X = 250
RIGHT_LANE_X = 350
LANES = [LEFT_LANE_X, CENTER_LANE_X, RIGHT_LANE_X]

# Drawing rectangles (x, y, width, height)
ROAD_RECT = (100, 0, ROAD_WIDTH, SCREEN_HEIGHT)
LEFT_EDGE_MARKER_RECT = (95, 0, MARKER_WIDTH, SCREEN_HEIGHT)
RIGHT_EDGE_MARKER_RECT = (395, 0, MARKER_WIDTH, SCREEN_HEIGHT)

# --- Game and Time Settings ---
clock = pygame.time.Clock()
FPS = 120                   # Refresh rate (Frames Per Second)

# --- Game State Variables (Initialized) ---
gameover = False
speed = 1.2                 # Initial scrolling speed (difficulty)
score = 0
lane_marker_move_y = 0      # Variable used for animating lane markers

# ==============================================================================
#  2. OBJECT CLASSES (SPRITES)
# ==============================================================================

class Vehicle(pygame.sprite.Sprite):
    """Base class for all vehicles (enemies), inheriting from Pygame's Sprite."""

    def __init__(self, image, x, y):
        pygame.sprite.Sprite.__init__(self)  # Initialize the sprite

        # Scale the image to fit correctly in the lane (45px width is target size)
        image_scale = 45 / image.get_rect().width
        new_width = image.get_rect().width * image_scale
        new_height = image.get_rect().height * image_scale
        self.image = pygame.transform.scale(image, (new_width, new_height))

        self.rect = self.image.get_rect()  # Create the collision rectangle
        self.rect.center = [x, y]  # Defines the initial position


class PlayerVehicle(Vehicle):
    """Specific class for the player's car."""

    def __init__(self, x, y):
        # Load the specific player image (Requires 'images/car.png')
        image = pygame.image.load('images/car.png')
        super().__init__(image, x, y)


# ==============================================================================
#  3. ASSET LOADING AND INITIAL SETUP
# ==============================================================================

player_group = pygame.sprite.Group()
vehicle_group = pygame.sprite.Group()

# Create the player's car and add it to the group
player = PlayerVehicle(PLAYER_START_X, PLAYER_START_Y)
player_group.add(player)

# Load enemy vehicle images
image_filenames = ['pickup_truck.png', 'semi_trailer.png', 'taxi.png', 'van.png']
vehicle_images = []
for image_filename in image_filenames:
    # Images must be in an 'images/' folder
    try:
        image = pygame.image.load('images/' + image_filename)
        vehicle_images.append(image)
    except pygame.error as e:
        # Better error handling for missing assets
        print(f"Error loading image: images/{image_filename}. Please check file path.")
        sys.exit()

# Load the crash image
try:
    crash = pygame.image.load('images/crash.png')
    crash_rect = crash.get_rect()
except pygame.error as e:
    print("Error loading crash image.")
    sys.exit()

# --- Utility Functions ---

def reset_game():
    """Resets all necessary global variables and clears groups for a new game."""
    global gameover, speed, score
    
    # 1. Reset Game State
    gameover = False
    speed = 1.2
    score = 0
    
    # 2. Clear Enemy Vehicles
    vehicle_group.empty() 
    
    # 3. Reposition the Player
    player.rect.center = [PLAYER_START_X, PLAYER_START_Y]


# ==============================================================================
#  4. MAIN GAME LOOP
# ==============================================================================

running = True
while running:

    clock.tick(FPS)  # Maintains the game frame rate

    # ----------------------------------------------------------------------
    # A. EVENT HANDLING (Input and Quit)
    # ----------------------------------------------------------------------
    
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False

        # Player movement (only upon key press and only if game is not over)
        if event.type == KEYDOWN and not gameover:

            # Move left: checks bounds using lane constants
            if event.key == K_LEFT and player.rect.center[0] > LEFT_LANE_X:
                player.rect.x -= 100
            # Move right: checks bounds using lane constants
            elif event.key == K_RIGHT and player.rect.center[0] < RIGHT_LANE_X:
                player.rect.x += 100

            # --- Side Swipe Collision Check ---
            # Immediately check if a side collision occurs after changing lanes.
            for vehicle in vehicle_group:
                if pygame.sprite.collide_rect(player, vehicle):
                    
                    gameover = True

                    # Adjusts the player position based on the impact direction for visual effect
                    if event.key == K_LEFT:
                        player.rect.left = vehicle.rect.right
                    elif event.key == K_RIGHT:
                        player.rect.right = vehicle.rect.left

                    # Centers the crash image between the two vehicles
                    crash_rect.center = [player.rect.center[0], (player.rect.center[1] + vehicle.rect.center[1]) / 2]


    # ----------------------------------------------------------------------
    # B. DRAWING THE WORLD (Rendering)
    # ----------------------------------------------------------------------
    
    # 1. Draw Static Background (Grass, Road, Edges)
    screen.fill(GREEN)
    pygame.draw.rect(screen, GRAY, ROAD_RECT)
    pygame.draw.rect(screen, YELLOW, LEFT_EDGE_MARKER_RECT)
    pygame.draw.rect(screen, YELLOW, RIGHT_EDGE_MARKER_RECT)

    # 2. Lane marker animation (Scrolling Illusion)
    # Use global variable lane_marker_move_y
    lane_marker_move_y += speed * 2
    if lane_marker_move_y >= MARKER_HEIGHT * 2:
        lane_marker_move_y = 0  # Reset for the infinite scrolling effect

    # Drawing white lines on the lanes
    for y in range(MARKER_HEIGHT * -2, SCREEN_HEIGHT, MARKER_HEIGHT * 2):
        # Center lane marker 1
        pygame.draw.rect(screen, WHITE, (LEFT_LANE_X + 45, y + lane_marker_move_y, MARKER_WIDTH, MARKER_HEIGHT))
        # Center lane marker 2
        pygame.draw.rect(screen, WHITE, (CENTER_LANE_X + 45, y + lane_marker_move_y, MARKER_WIDTH, MARKER_HEIGHT))

    # 3. Draw Player
    player_group.draw(screen)

    # ----------------------------------------------------------------------
    # C. GAME LOGIC (Movement and Spawning)
    # ----------------------------------------------------------------------

    if not gameover:
        # Add a new vehicle if there are less than 2 on screen and space permits
        if len(vehicle_group) < 2:
            add_vehicle = True
            # Check that there is enough space between existing vehicles (to prevent stacking)
            for vehicle in vehicle_group:
                if vehicle.rect.top < vehicle.rect.height * 1.5:
                    add_vehicle = False

            if add_vehicle:
                lane = random.choice(LANES)             # Random lane selection
                image = random.choice(vehicle_images)   # Random image selection
                # The vehicle appears just above the screen (height / -2)
                vehicle = Vehicle(image, lane, SCREEN_HEIGHT / -2) 
                vehicle_group.add(vehicle)

        # Movement and handling of vehicles leaving the screen
        for vehicle in vehicle_group:
            vehicle.rect.y += speed  # Move the vehicle downwards based on speed

            # Check if the vehicle has successfully left the bottom
            if vehicle.rect.top >= SCREEN_HEIGHT:
                vehicle.kill()  # Delete the sprite
                score += 1      # Increase the score

                # Increase speed (difficulty) every 5 points
                if score > 0 and score % 5 == 0:
                    speed += 1

        # Draw the enemy vehicles
        vehicle_group.draw(screen)

        # Display the score
        font = pygame.font.Font(pygame.font.get_default_font(), 16)
        text = font.render(f'Score: {score} | Speed: {speed:.1f}', True, WHITE)
        text_rect = text.get_rect()
        text_rect.topleft = (10, 10) # Position in the top left corner
        screen.blit(text, text_rect)

        # --- HEAD-ON COLLISION CHECK ---
        # Check if the player collides with an enemy vehicle
        if pygame.sprite.spritecollide(player, vehicle_group, True):  # 'True' deletes the enemy vehicle
            gameover = True
            # Position the crash image on the player
            crash_rect.center = [player.rect.center[0], player.rect.top]


    # ----------------------------------------------------------------------
    # D. GAME OVER DISPLAY AND PAUSE LOOP
    # ----------------------------------------------------------------------

    if gameover:
        screen.blit(crash, crash_rect)  # Display the crash image

        # Draw a red banner for the message
        pygame.draw.rect(screen, RED, (0, 50, SCREEN_WIDTH, 100))

        # Display the game over message
        font = pygame.font.Font(pygame.font.get_default_font(), 16)
        text = font.render('Game over. Play again? (Press Y or N)', True, WHITE)
        text_rect = text.get_rect()
        text_rect.center = (SCREEN_WIDTH / 2, 100)
        screen.blit(text, text_rect)


    pygame.display.update()  # Update the entire screen

    # --- WAIT LOOP (GAME PAUSED) ---
    # The game is frozen here, waiting for the player to press Y or N
    while gameover:

        clock.tick(FPS)  # Maintain FPS even when paused

        for event in pygame.event.get():
            if event.type == QUIT:
                gameover = False
                running = False
            
            if event.type == KEYDOWN:
                if event.key == K_y:
                    # Reset variables to play again
                    reset_game()
                    gameover = False # Exit the 'while gameover' loop
                elif event.key == K_n:
                    # Exit the program completely
                    gameover = False
                    running = False


# ==============================================================================
#  5. EXIT
# ==============================================================================

pygame.quit() # Quit Pygame at the end of the main loop
sys.exit()    # Ensure the Python process terminates cleanly