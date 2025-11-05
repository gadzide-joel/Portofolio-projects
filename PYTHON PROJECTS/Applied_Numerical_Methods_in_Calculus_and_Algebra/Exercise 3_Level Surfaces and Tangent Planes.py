"""
Project: Level_Surface_Tangent_Plane
Exercise 3: Level Surfaces and Tangent Planes

Goal: Visualize the 3D level surface defined by g(x,y,z)=10 where g(x,y,z) = x² + y² + z³.
Then, calculate the tangent plane at a specific point B(3, 0, 1) using the gradient ∇g, and plot both surfaces.
"""

        # ------------------------
             # EXERCISE 3
        # ------------------------

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function for the level surface g(x,y,z) = x² + y² + z³
def g(x, y, z):
    return x**2 + y**2 + z**3

# Create the grid
x = np.linspace(-3, 3, 100)
y = np.linspace(-3, 3, 100)
X, Y = np.meshgrid(x, y)

# Z must satisfy g(x,y,z) = 10, so z³ = 10 - x² - y²
Z_arg = 10 - (X**2 + Y**2)
# Calculate Z (using cube root)
Z = np.cbrt(Z_arg)

# Figure 1: Level Surface
fig1 = plt.figure(figsize=(8, 8))
ax1 = fig1.add_subplot(111, projection='3d')
ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
ax1.set_title('Level Surface $g(x,y,z)=10$')
ax1.set_xlabel('x'); ax1.set_ylabel('y'); ax1.set_zlabel('z')
plt.show()

# --- TANGENT PLANE CALCULATION at point B(3, 0, 1) ---
# Gradient ∇g = (2x, 2y, 3z²)
# Gradient at B(3, 0, 1): ∇g(3, 0, 1) = (6, 0, 3)
# Tangent plane equation: 6(x - 3) + 0(y - 0) + 3(z - 1) = 0 => z = -2x + 7

# Calculate the tangent plane (Z_plane)
Z_plan = -2 * X + 7

# Figure 2: Surface and Tangent Plane
fig2 = plt.figure(figsize=(8, 8))
ax2 = fig2.add_subplot(111, projection='3d')

# Plot the level surface
ax2.plot_surface(X, Y, Z, cmap='viridis', alpha=0.5, label='$g(x,y,z)=10$')

# Plot the tangent plane
ax2.plot_surface(X, Y, Z_plan, cmap='plasma', alpha=0.7, label='Tangent Plane at B(3,0,1)')

# Plot the point B
ax2.scatter(3, 0, 1, color='red', s=100, label='B(3, 0, 1)')

ax2.set_title('Tangent Plane at B(3,0,1) to $g(x,y,z)=10$')
ax2.set_xlabel('x'); ax2.set_ylabel('y'); ax2.set_zlabel('z')
plt.show()