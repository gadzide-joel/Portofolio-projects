"""
Project: Gradient_Descent_Optimization
Exercise 2: Gradient Descent

Goal: Visualize the function f(x,y) = (x + y)(y + 1) as a 3D surface and its level curves (Isotherms).
Then, perform Gradient Descent starting from an initial point to find the local minimum,
plotting the convergence trajectory on the level curves.
"""

        # ------------------------
             # EXERCISE 2
        # ------------------------


import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define the temperature function
def f(x, y):
    return (x + y) * (y + 1) # f(x,y) = xy + x + y² + y

# Create the grid
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)

# === FIGURE 1: 3D Surface and Level Curves (Isotherms) ===
fig = plt.figure(figsize=(12, 6))

# Left part: 3D surface
ax = fig.add_subplot(121, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
ax.set_zlabel('Temperature (°C)')
ax.set_title('Temperature Surface $f(x,y)$')

# Right part: Level curves (Isotherms)
ax2 = fig.add_subplot(122)
levels = [-10, 0, 10, 20] # Isotherms (lines of constant temperature)
contour = ax2.contour(X, Y, Z, levels=levels, colors='k')
ax2.clabel(contour, inline=True, fontsize=10)
ax2.set_xlabel('$x$')
ax2.set_ylabel('$y$')
ax2.set_title('Isotherm Curves')
ax2.grid(True)

plt.tight_layout()
plt.show()

# === GRADIENT DESCENT IMPLEMENTATION ===

# Define the gradient of f
# ∇f = (∂f/∂x, ∂f/∂y) = (y + 1, x + 2y + 1)
def gradient(x, y):
    df_dx = y + 1
    df_dy = x + 2 * y + 1
    return np.array([df_dx, df_dy])

# Initial point and parameters
x, y = 3.0, 5.0
learning_rate = 0.1 # Learning rate (step size)
iterations = 8

# List to store the trajectory
trajectory = [(x, y)]

print("\n=== Gradient Descent ===")
for i in range(iterations):
    grad = gradient(x, y)
    # Move in the opposite direction of the gradient
    x -= learning_rate * grad[0]
    y -= learning_rate * grad[1]
    trajectory.append((x, y))
    print(f"Iteration {i+1}: x={x:.4f}, y={y:.4f}, f(x,y)={f(x, y):.4f}")

# Plotting the descent trajectory on the level curves
traj_x, traj_y = zip(*trajectory)

plt.figure(figsize=(8, 8))
levels = np.linspace(np.min(Z), np.max(Z), 20) # More levels for background
plt.contourf(X, Y, Z, levels=levels, cmap='viridis', alpha=0.5)
plt.contour(X, Y, Z, levels=levels, colors='k', linewidths=0.5)

# Plot the trajectory
plt.plot(traj_x, traj_y, 'r-o', label='Descent Trajectory', linewidth=2, markersize=5)
plt.plot(traj_x[0], traj_y[0], 'go', label='Start (3, 5)', markersize=8)
plt.plot(traj_x[-1], traj_y[-1], 'ro', label='End', markersize=8)

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.title('Gradient Descent Trajectory on Isotherms')
plt.grid(True)
plt.axis('equal')
plt.legend()
plt.show()
