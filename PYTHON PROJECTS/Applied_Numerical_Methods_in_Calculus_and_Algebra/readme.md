## Applied Mathematics and Numerical Visualization

This project demonstrates core concepts from Linear Algebra, Multivariable Calculus, and Optimization using Python, NumPy, and Matplotlib.

It is structured into four exercises, each focusing on a distinct mathematical visualization technique.

### 1\. Norm Spaces (L\_1 and L\_2)

* **Goal:** Visualize the unit balls (spheres) defined by the Euclidean (L\_2) and Manhattan (L\_1) norms in 2D.
* **Visualization:** The L\_2 norm creates a **circle** (the standard sphere), while the L\_1 norm creates a **diamond** (a square rotated by 45 degrees).
* **Key Concept:** Illustrates how different norms affect the measurement of distance and the shape of unit balls.

### 2\. Gradient Descent Optimization

* **Goal:** Visualize a 3D function surface, its level curves (isotherms), and perform **Gradient Descent** to find a local minimum.
* **Function:** f(x,y) = (x + y)(y + 1), representing a "temperature surface."
* **Visualization:** Plots the 3D surface and the 2D level curves. The descent trajectory is plotted on the isotherms, showing the algorithm converging to the minimum by following the direction opposite to the **gradient** nabla f.

### 3\. Level Surfaces and Tangent Planes

* **Goal:** Visualize a **level surface** in 3D and calculate and plot the **tangent plane** at a specific point.
* **Function:** g(x,y,z) = x^2 + y^2 + z^3 = 10.
* **Methodology:** The gradient nabla g is calculated at the point $B(3, 0, 1) to determine the normal vector required for the tangent plane equation.

### 4\. Domain of Functions

* **Goal:** Graphically determine and visualize the valid input domains (regions in the xy-plane) for two different functions.
* **Function Examples:**

  * f(x,y) = \\sqrt{1 - (x^2 + y^2)}: Domain is the **closed unit disk** (x^2 + y^2 \\le 1).
  * h(x,y) = \\ln(y) / \\sqrt{x^2 + y^2 - 1}: Domain is the region where y > 0 AND x^2 + y^2 > 1 (Upper half-plane, outside the open unit circle).





**Note:** I have included the corresponding graphic files for each code exercise in this directory.

