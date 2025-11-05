"""
Project: Norms_L1_L2_Visualization
Exercise 1: Norms (L1 and L2)

Goal: Visualize the unit balls (spheres) defined by the Euclidean (L2) and Manhattan (L1) norms in 2D.
The L2 norm results in a circle, and the L1 norm results in a diamond shape.
"""

        # ------------------------
             # EXERCISE 1
        # ------------------------


import numpy as np
import matplotlib.pyplot as plt

# Create a figure with two subplots
plt.figure(figsize=(10, 5))

# ---------------------------
# Euclidean Norm (L2) - Circle
# ---------------------------
plt.subplot(1, 2, 1)  # 1 row, 2 columns, 1st graph

# Plot the unit sphere (radius 1)
x1 = []
y1 = []
for t in range(0, 361):  # from 0 to 360 degrees
    angle = t * np.pi / 180
    x1.append(1 * np.cos(angle))
    y1.append(1 * np.sin(angle))

# Plot the sphere with radius 1.5
x2 = []
y2 = []
for t in range(0, 361):
    angle = t * np.pi / 180
    x2.append(1.5 * np.cos(angle))
    y2.append(1.5 * np.sin(angle))

# Display the circles
plt.plot(x1, y1, label="Unit Sphere ($L_2$ norm)")
plt.plot(x2, y2, label="Sphere radius 1.5 ($L_2$ norm)")

# Straight trajectory between the two spheres
sqrt2_inv = 1 / np.sqrt(2)
plt.plot([sqrt2_inv, 1.5 * sqrt2_inv], [sqrt2_inv, 1.5 * sqrt2_inv], 'r--', label="Radial Trajectory")

plt.title("Euclidean Norm ($L_2$)")
plt.axis('equal')
plt.grid(True)
plt.legend()

# --------------------------
# Manhattan Norm (L1) - Diamond
# --------------------------
plt.subplot(1, 2, 2)  # 1 row, 2 columns, 2nd graph

# Define the unit ball for L1: |x| + |y| = 1
# Vertices: (1, 0), (0, 1), (-1, 0), (0, -1)
x_l1 = [1, 0, -1, 0, 1]
y_l1 = [0, 1, 0, -1, 0]
plt.plot(x_l1, y_l1, 'b-', label="Unit Ball ($L_1$ norm)")

# Define the ball for L1 with radius 1.5: |x| + |y| = 1.5
x_l1_1_5 = [1.5, 0, -1.5, 0, 1.5]
y_l1_1_5 = [0, 1.5, 0, -1.5, 0]
plt.plot(x_l1_1_5, y_l1_1_5, 'g-', label="Ball radius 1.5 ($L_1$ norm)")

# Straight trajectory (same as L2)
plt.plot([sqrt2_inv, 1.5 * sqrt2_inv], [sqrt2_inv, 1.5 * sqrt2_inv], 'r--', label="Radial Trajectory")

plt.title("Manhattan Norm ($L_1$)")
plt.axis('equal')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()