"""
Project Summary: 3D Graphical Visualization and Level Curves

This Python script uses NumPy and Matplotlib to graphically represent two mathematical functions of two variables:
1. f(x,y) = x² + y² (Paraboloid)
2. g(x,y) = |x| + |y| (Square Pyramid)

The program executes three main tasks:
1. 3D Representation: Displays the surfaces of f(x,y) and g(x,y) on separate 3D axes.
2. Level Curves of f: Plots the level curves of f(x,y) (which are circles) for specific k values.
3. Level Curves of g: Plots the level curves of g(x,y) (which are squares/diamonds) for specific k values.
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# --- 1. 3D Representation of functions f and g on separate axes ---
def plot_functions():
    fig = plt.figure(figsize=(12, 6))
    
    # Create grids for x and y
    x = np.linspace(-4, 4, 100)
    y = np.linspace(-4, 4, 100)
    X, Y = np.meshgrid(x, y)
    
    # Calculate the functions
    Z_f = X**2 + Y**2       # f(x,y) = x² + y²
    Z_g = np.abs(X) + np.abs(Y) # g(x,y) = |x| + |y|
    
    # 3D Graph for f (Paraboloid)
    ax1 = fig.add_subplot(121, projection='3d')
    ax1.plot_surface(X, Y, Z_f, cmap='viridis')
    ax1.set_title('$f(x,y) = x^2 + y^2$')
    ax1.set_xlabel('x')
    ax1.set_ylabel('y')
    ax1.set_zlabel('z')
    
    # 3D Graph for g (Square Pyramid)
    ax2 = fig.add_subplot(122, projection='3d')
    ax2.plot_surface(X, Y, Z_g, cmap='plasma')
    ax2.set_title('$g(x,y) = |x| + |y|$')
    ax2.set_xlabel('x')
    ax2.set_ylabel('y')
    ax2.set_zlabel('z')
    
    plt.suptitle("3D Representation of functions f and g")
    plt.tight_layout()
    plt.show()

# --- 2. Level Curves of f for k ∈ {1, 4, 9, 16} (Circles) ---
def plot_level_curves_f():
    plt.figure(figsize=(8, 8))
    
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    Z = X**2 + Y**2
    
    levels = [1, 4, 9, 16]
    cs = plt.contour(X, Y, Z, levels=levels, colors='blue')
    plt.clabel(cs, inline=True, fontsize=10)
    
    plt.title('Level Curves of $f(x,y) = x^2 + y^2$')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.axis('equal') # Important for circles to look circular
    plt.show()

# --- 3. Level Curves of g for k ∈ {1, 2, 3, 4} (Squares/Diamonds) ---
def plot_level_curves_g():
    plt.figure(figsize=(8, 8))
    
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    Z = np.abs(X) + np.abs(Y)
    
    levels = [1, 2, 3, 4]
    cs = plt.contour(X, Y, Z, levels=levels, colors='red')
    plt.clabel(cs, inline=True, fontsize=10)
    
    plt.title('Level Curves of $g(x,y) = |x| + |y|$') 
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.axis('equal')
    plt.show()

# Execute all plot functions
plot_functions()
plot_level_curves_f()
plot_level_curves_g()