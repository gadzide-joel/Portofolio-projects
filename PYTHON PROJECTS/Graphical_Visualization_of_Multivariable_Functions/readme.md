## Multivariable Function Visualization

This Python project uses NumPy and Matplotlib to illustrate two key methods of visualizing multivariable functions (functions of two variables, f(x, y)).

The script focuses on two specific functions:
1. f(x, y) = x² + y² (The Paraboloid)
2. g(x, y) = |x| + |y| (The Square Pyramid / Cone)

### Key Features and Tasks

1. **3D Surface Representation:**
* Plots the 3D surfaces of both f(x, y) and g(x, y) on separate axes, showing their characteristic shapes (Paraboloid and Pyramid).
* Uses mpl_toolkits.mplot3d for the visualization. 

2. **Level Curves Analysis:**
* **Level Curves of f:** Plots the curves where f(x, y) equals a constant k (k = 1, 4, 9, 16). For x² + y² = k, these curves are **circles**. 
* **Level Curves of g:** Plots the curves where g(x, y) equals a constant k (k = 1, 2, 3, 4). For |x| + |y| = k, these curves are **squares or diamonds**. 

### Visualization Methods Demonstrated

| Function | 3D Shape | Level Curves Shape |
| :--- | :--- | :--- |
| **f(x, y) = x² + y²** | Paraboloid | Circles (Concentric) |
| **g(x, y) = |x| + |y|** | Square Pyramid | Squares / Diamonds |

Note: I have included the corresponding graphic files for each code exercise in this directory.