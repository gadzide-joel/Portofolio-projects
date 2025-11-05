# Applied_Kinematics_Analysis.py
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.integrate import quad

# ==============================================================================
#                               PROGRAM SUMMARY
# ==============================================================================
"""
This Python script demonstrates expertise in **computational physics and advanced plotting** by analyzing the kinematic motion of a particle in both 2D (planar) and 3D space. 
The project showcases proficiency in the following areas:

1.  **Parametric Trajectory Plotting:** Visualizing complex particle paths in 2D 
    and 3D defined by time-dependent position vectors. 
2.  **Vector Field Analysis:** Calculating and visualizing the **velocity vector field** along the particle's trajectory using the `quiver` function, which is fundamental 
    to fluid dynamics and field theory.
3.  **Numerical Integration:** Employing the `scipy.integrate.quad` function to 
    accurately compute the **arc length (distance traveled)**, which requires 
    integrating the norm of the velocity vector (speed) over a specified time interval.

This project validates a strong foundation in applying high-level mathematical 
libraries (NumPy, Matplotlib, SciPy) to solve problems in classical mechanics, 
a critical skill for research in engineering and computational science.
"""
# ==============================================================================

# --- Project 1: Particle Kinematics Analysis ---

## PART A: 2D Planar Trajectory

# 1. Trajectory Plotting between t=2 and t=5
print("\n--- Part A: 2D Planar Trajectory Analysis ---")
t = np.linspace(2, 5, 1000)
x = np.cos(-t)
y = np.sin(2 * t)

plt.figure(figsize=(8, 6))
plt.plot(x, y, label="Trajectory from t=2 to t=5")
plt.scatter([np.cos(-2)], [np.sin(4)], color='red', marker='o', label='Start Point (t=2)')
plt.scatter([np.cos(-5)], [np.sin(10)], color='green', marker='o', label='End Point (t=5)')
plt.title("2D Particle Trajectory (Part A)")
plt.xlabel("x-coordinate")
plt.ylabel("y-coordinate")
plt.grid(True)
plt.legend()
plt.show()

# 2. Velocity Vector Field Plot
# Position: r(t) = (cos(-t), sin(2t))
# Velocity: v(t) = (d/dt(cos(-t)), d/dt(sin(2t))) = (-sin(-t) * (-1), 2cos(2t))
#           v(t) = (sin(t), 2cos(2t))
T_quiver = np.linspace(2, 5, 30)  # Discrete points for vector field
X_pos = np.cos(-T_quiver)
Y_pos = np.sin(2 * T_quiver)
U_vel = np.sin(T_quiver)          # x-component of velocity (v_x = sin(t))
V_vel = 2 * np.cos(2 * T_quiver)  # y-component of velocity (v_y = 2cos(2t))

plt.figure(figsize=(8, 6))
plt.plot(x, y, label="Trajectory", color='gray')
# Plot velocity vectors (quiver plot)
plt.quiver(X_pos, Y_pos, U_vel, V_vel, color='blue', scale=10, scale_units='xy', 
           angles='xy', label="Velocity Vectors") 
plt.title("Velocity Vector Field along the 2D Trajectory")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.show()

# 3. Calculation of Total Distance Traveled (Arc Length L)
# Arc Length L = Integral from t1 to t2 of ||v(t)|| dt
# Speed ||v(t)|| = sqrt(v_x^2 + v_y^2) = sqrt(sin^2(t) + (2cos(2t))^2)
def speed_norm(t):
    # Note: sin(-t) = -sin(t), so sin^2(-t) = sin^2(t).
    return np.sqrt(np.sin(t)**2 + 4 * np.cos(2 * t)**2)

# Use scipy.integrate.quad for numerical integration
L, error = quad(speed_norm, 2, 5)

print(f"Total distance traveled between t=2 and t=5 is: L = {L:.4f} units (Integration Error: {error:.2e})")

# ---

## PART B: 3D Trajectory Analysis

# Trajectory 3D between t=0 and t=5.8
print("\n--- Part B: 3D Trajectory Analysis ---")
t_3d = np.linspace(0, 5.8, 1000)
x_3d = np.cos(t_3d)
y_3d = -np.sin(2 * t_3d + np.pi/3)
z_3d = t_3d**2

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x_3d, y_3d, z_3d, label="Trajectory from t=0 to t=5.8", color='purple')
ax.scatter([np.cos(0)], [-np.sin(np.pi/3)], [0], color='red', marker='o', s=50, label='Start (t=0)')
ax.scatter([np.cos(5.8)], [-np.sin(2 * 5.8 + np.pi/3)], [5.8**2], color='green', marker='o', s=50, label='End (t=5.8)')
ax.set_title("3D Particle Trajectory in (O,i,j,k) Frame (Part B)")
ax.set_xlabel("x-axis")
ax.set_ylabel("y-axis")
ax.set_zlabel("z-axis")
ax.legend()
plt.show()
