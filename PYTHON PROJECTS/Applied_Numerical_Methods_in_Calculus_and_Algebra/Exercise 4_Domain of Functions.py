"""
Project: Function_Domain_Visualization
Exercise 4: Domain of Functions

Goal: Graphically determine and visualize the valid input domains (regions in the xy-plane) for two functions:
1. f(x,y) = sqrt(1 - (x² + y²)): Domain is the closed unit disk (x² + y² ≤ 1).
2. h(x,y) = ln(y) / sqrt(x² + y² - 1): Domain is the upper half-plane (y > 0) outside the open unit disk (x² + y² > 1).
"""

       # ------------------------
             # EXERCISE 4
        # ------------------------


import numpy as np
import matplotlib.pyplot as plt

# --- 1. Domain of f(x,y) = sqrt(1 - (x² + y²)) ---
# Condition: x² + y² ≤ 1 (Closed unit disk)
x = np.linspace(-1, 1, 200)
y = np.linspace(-1, 1, 200)
X, Y = np.meshgrid(x, y)

# Calculate Z to define the boundary
Z = np.sqrt(np.maximum(1 - (X**2 + Y**2), 0))

plt.figure(figsize=(6, 6))
# Use contourf to fill the domain area
plt.contourf(X, Y, Z, levels=20, cmap='viridis')
# Plot the boundary (the unit circle)
circle = plt.Circle((0, 0), 1, color='black', fill=False, linewidth=2)
plt.gca().add_artist(circle)
plt.title('Domain of $f(x,y)=\\sqrt{1-(x^2+y^2)}$: $x^2 + y^2 \\le 1$')
plt.xlabel('x'); plt.ylabel('y')
plt.gca().set_aspect('equal')
plt.grid(True)
plt.show()


# --- 2. Domain of h(x,y) = ln(y) / sqrt(x² + y² - 1) ---
# Combined Conditions: y > 0 AND x² + y² > 1
x = np.linspace(-2, 2, 200)
y = np.linspace(0.001, 2, 200)  # y > 0 strict
X, Y = np.meshgrid(x, y)

# Logical mask for the domain
condition = (Y > 0) & (X**2 + Y**2 > 1)

plt.figure(figsize=(6, 6))
# Scatter plot of points satisfying the condition
plt.scatter(X[condition], Y[condition], s=1, color='blue')

# Plot the boundaries (x² + y² = 1 and y = 0)
# 1. Circle boundary (x² + y² = 1) - Dotted line as it is excluded
t_circ = np.linspace(0, np.pi, 100) # Only upper half-circle (y >= 0)
plt.plot(np.cos(t_circ), np.sin(t_circ), 'k--', label='Boundary $x^2+y^2=1$ (Excluded)')

# 2. x-axis boundary (y = 0) - Dotted line as it is excluded
plt.axhline(0, color='r', linestyle=':', label='Boundary $y=0$ (Excluded)')


plt.title('Domain of $h(x,y)$: $y > 0$ and $x^2 + y^2 > 1$')
plt.xlabel('x'); plt.ylabel('y')
plt.xlim(-2, 2); plt.ylim(0, 2)
plt.gca().set_aspect('equal')
plt.legend()
plt.grid(True)
plt.show()
