"""
Code Summary:
Numerical Solution: Solves the nonlinear implicit closure equation F(α, β) = 0 for the 
output angle α over a range of input angle β, using a custom iterative Newton's method. 
Multiple Solutions: Uses two distinct initial guesses (x₀ = 2π/3 and x₀ = -1) to 
demonstrate and plot the two separate kinematic configurations (solution branches) 
inherent to the four-bar mechanism.
"""

import numpy as np
import matplotlib.pyplot as plt

# Data (Link dimensions for the mechanical system)
a1 = 10  # cm
a2 = 13  # cm
a3 = 8   # cm
a4 = 10  # cm

# Define the function F(alpha, beta) (Equation F(α)=0 from the PDF)
def f(alpha, beta):
    # Constant term: (a1² + a2² - a3² + a4²) / (2 * a2 * a4)
    constant_term = (a1**2 + a2**2 - a3**2 + a4**2) / (2 * a2 * a4) 
    return (a1 / a2) * np.cos(beta) - (a1 / a4) * np.cos(alpha) - np.cos(alpha - beta) + constant_term

# Define the derivative F'(alpha, beta) (df/dalpha, used for Newton's method)
def df(alpha, beta):
    return (a1 / a4) * np.sin(alpha) + np.sin(alpha - beta)

# Improved Newton's method implementation
def newton_method(beta, x0, tol=1e-6, max_iter=100):
    x = x0
    for i in range(max_iter):
        fx = f(x, beta)
        dfx = df(x, beta)
        # Check if the derivative is too small to avoid division by zero
        if abs(dfx) < 1e-12:
            return np.nan # Return NaN if the derivative is near zero
        # Update x
        x_new = x - fx / dfx
        # Check for convergence
        if abs(x_new - x) < tol:
            # Final check: is the solution F(x) close to zero?
            if abs(f(x_new, beta)) < tol * 10:
                return x_new
            else:
                return np.nan # Did not converge to the root
        x = x_new
    return np.nan # Did not converge within max iterations

# Range of Beta values to test (converted to radians for calculation)
betas_deg = np.linspace(0, 180, 20)
betas = np.radians(betas_deg)

# Containers for the solutions
va1 = []
va2 = []

print("--- Solutions for alpha using two initial guesses ---")
print("beta (rad) | alpha (x₀=2π/3) | alpha (x₀=-1)")

# Loop through each beta value
for beta in betas:
    # Solve for alpha using the two initial guesses (x0) mentioned in the problem
    alpha1 = newton_method(beta, 2 * np.pi / 3)
    alpha2 = newton_method(beta, -1)
    
    # Format output, handling NaNs
    alpha1_str = f"{alpha1:.4f}" if not np.isnan(alpha1) else "NaN"
    alpha2_str = f"{alpha2:.4f}" if not np.isnan(alpha2) else "NaN"
    
    # Print the table row
    print(f"{beta:.4f} | {alpha1_str:>14} | {alpha2_str:>14}") 
    
    va1.append(alpha1)
    va2.append(alpha2)

# Convert to arrays for plotting
va1 = np.array(va1)
va2 = np.array(va2)

# Create the graph
plt.figure(figsize=(10, 6))

# Mask NaN points for better visualization
mask1 = ~np.isnan(va1)
mask2 = ~np.isnan(va2)

# Plot valid solutions (beta in degrees, alpha in degrees)
plt.plot(betas_deg[mask1], np.degrees(va1[mask1]), 'o-', color='dodgerblue', label='x₀ = 2π/3', markersize=6, linewidth=1.5)
plt.plot(betas_deg[mask2], np.degrees(va2[mask2]), 's-', color='crimson', label='x₀ = -1', markersize=6, linewidth=1.5)

# Plot customization
plt.title('Solutions for α as a function of β (using Newton\'s Method)')
plt.xlabel("β (degrees)")
plt.ylabel("α (degrees)")
plt.legend()
plt.grid(True)
plt.show()

print("\nAnalysis: The graph shows the two branches of solutions for the angle α depending on the initial guess x₀ for the Newton method.")