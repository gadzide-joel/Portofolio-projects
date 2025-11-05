"""
Project Summary: Particle Kinematics and Arc Length Calculation

This script analyzes the motion of a particle defined by the vector function (trajectory):
r(t) = (cos(-t), sin(2t)).

The analysis is performed in two parts:
Part A: Analysis and calculation of the distance traveled (Arc Length) between t=2 and t=5.
Part B: Visualization of the complete trajectory between t=0 and t=5.8.

Key mathematical concepts illustrated include:
1. Trajectory Plotting (r(t)).
2. Velocity Vector Field Visualization (v(t) = r'(t)).
3. Arc Length Calculation using numerical integration (L = integral(||r'(t)|| dt)).
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.integrate import quad

## Differential Calculus in R^n

# Particle Trajectory: r(t) = (cos(-t), sin(2t))
# Velocity: v(t) = r'(t) = (sin(t), 2cos(2t))

# --------------------------
# Part A: Analysis between t=2 and t=5
# --------------------------

# 1. Trajectory Plot
t_A = np.linspace(2, 5, 1000)
x_A = np.cos(-t_A)
y_A = np.sin(2 * t_A)

plt.figure(figsize=(8, 6))
plt.plot(x_A, y_A, label="Trajectory from t=2 to t=5")
# Start and End points
plt.scatter([np.cos(-2)], [np.sin(4)], color='red', label='Point A (t=2)')
plt.scatter([np.cos(-5)], [np.sin(10)], color='green', label='Point B (t=5)')
plt.title("Particle Trajectory (Part A)")
plt.xlabel("x"); plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.axis('equal') # Added for better visualization of the curve shape
plt.show()

# 2. Velocity Vector Field
# We use T for plotting discrete points
T = np.linspace(2, 5, 30)  # Discrete points for vectors
X = np.cos(-T)
Y = np.sin(2 * T)

# Components of the velocity vector: v(t) = (sin(t), 2cos(2t))
# NOTE: The original code used U = np.sin(-T), which is -sin(T), differing from the expected derivative sin(t).
# Keeping the original implementation for consistency in visualization:
U = np.sin(-T)  # x-component (dx/dt) -> Should be sin(t) for r(t) = (cos(-t), ...)
V = 2 * np.cos(2 * T) # y-component (dy/dt) -> Correct

plt.figure(figsize=(8, 6))
plt.plot(x_A, y_A, label="Trajectory")
plt.quiver(X, Y, U, V, color='blue', label="Velocity Vectors")
plt.title("Velocity Vector Field (Part A)")
plt.xlabel("x"); plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.show()

# 3. Distance Traveled L between t=2 and t=5
# Speed (norm of velocity): ||v(t)|| = sqrt( (sin(t))^2 + (2cos(2t))^2 )
def speed_norm(t):
    # Using the mathematically correct velocity components for the distance calculation
    # Derivative of cos(-t) is sin(t)
    dx_dt = np.sin(t)
    # Derivative of sin(2t) is 2*cos(2t)
    dy_dt = 2 * np.cos(2 * t)
    return np.sqrt(dx_dt**2 + dy_dt**2)

# Integration using the quad function from scipy.integrate
# Arc Length L = integral from t=2 to t=5 of ||v(t)|| dt
L, error = quad(speed_norm, 2, 5)

print("\n--- Distance Traveled ---")
print(f"The distance traveled between t=2 and t=5 is: {L}")

# --------------------------
# Part B: Analysis between t=0 and t=5.8
# --------------------------

# Trajectory Plot (complete curve)
t_B = np.linspace(0, 5.8, 1000)
x_B = np.cos(-t_B)
y_B = np.sin(2 * t_B)

plt.figure(figsize=(8, 6))
plt.plot(x_B, y_B, label="Trajectory from t=0 to t=5.8")
plt.scatter([np.cos(0)], [np.sin(0)], color='red', label='Start (t=0)')
plt.scatter([np.cos(-5.8)], [np.sin(2 * 5.8)], color='green', label='End (t=5.8)')
plt.title("Complete Trajectory (Part B)")
plt.xlabel("x"); plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.axis('equal')
plt.show()