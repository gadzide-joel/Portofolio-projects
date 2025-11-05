#### Python code for the L(α) graph

"""
Code Summary:
Visualization: Defines the complex trigonometric function L(alpha) and uses 
Matplotlib to plot L(alpha) vs. alpha (in degrees). The plot visually confirms 
the existence of a single global minimum, establishing the basis for optimization.
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import newton # Imported later in the original file

# Data
l1 = 1      # in meters
l2 = 1.5    # in meters
gamma_deg = 120
gamma = np.radians(gamma_deg)

# Function L(α)
def L(alpha):
    return l1 / np.sin(alpha) + l2 / np.sin(np.pi - gamma - alpha)

# Plotting L(α)
alpha_vals = np.linspace(0.01, np.pi - gamma - 0.01, 500)
L_vals = L(alpha_vals)

plt.figure(figsize=(8, 5))
plt.plot(np.degrees(alpha_vals), L_vals, label='L(α)', color='orange')
plt.xlabel("α (degrees)")
plt.ylabel("L(α) in m")
plt.title("Graph of the function L(α)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()


#### Code for Newton's method

"""
Code Summary:
Optimization: Solves the minimization problem by finding the root of the function's 
first derivative, L'(alpha), using the Newton-Raphson method (via scipy.optimize.newton). 
The result yields the optimal angle α_min and the corresponding minimum length L_min 
(which is the Maximum vehicle length L_max).
"""

# Parameters
l1 = 1.0  # m
l2 = 1.5  # m
gamma = 120 * np.pi / 180  # 120° in radians

# Redefinition of the function L(alpha) (using the alternative formula)
# Note: The code actually uses the derivative L_prime(alpha) for the root finding.
def L(alpha):
    return l1 / np.sin(alpha) + l2 / np.sin(gamma + alpha) 

# First derivative of L(alpha) (L'(alpha), the function whose root we seek)
def L_prime(alpha):
    # This formula is L'(α) = -l1*cot(α)/sin(α) - l2*cot(γ+α)/sin(γ+α)
    return -l1 * np.cos(alpha) / np.sin(alpha)**2 + l2 * np.cos(gamma + alpha) / np.sin(gamma + alpha)**2

# Initial guess (e.g., in the middle of the valid range)
alpha_guess = (np.pi - gamma) / 2
print(f"\nSearching for the root of L'(α) using Newton's method with initial guess {np.degrees(alpha_guess):.2f}°")

# Find the root of L'(alpha) to get the angle α_min that minimizes L(α)
alpha_min = newton(L_prime, alpha_guess, maxiter=100) 

# Calculate the minimum length L_min (which is the Maximum vehicle length L_max)
L_min = L(alpha_min)

print(f"The optimal angle α is: {np.degrees(alpha_min):.4f} degrees ({alpha_min:.4f} radians)")
print(f"The Minimum Length L_min (Maximum vehicle length L_max) is: {L_min:.4f} m")

# Verification: The minimal length L_min is the maximal admissible length L_max.
# Final result: L_max = {L_min:.4f} m