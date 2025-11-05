Kinematic and Numerical Analysis

This Python project contains two distinct scripts demonstrating the application of numerical methods (plotting and Newton's method) to solve engineering problems in geometry and mechanical design.

1. Optimal Length Calculation (Function L(alpha))

This section addresses an optimization problem to determine the minimum length, L\_min, required for an object (e.g., a vehicle) to navigate a corner defined by fixed dimensions (l\_1, l\_2) and an angle (gamma). This minimum length is the Maximum Admissible Length (L\_max) for that turn.

Goal: Find the angle alpha\_min that minimizes the function L(alpha).
Methodology:

* Graphical Analysis: Plotting L(alpha) to visualize the minimum.
* Newton's Method: Used to find the precise root of the first derivative, L'(alpha), which corresponds to the optimal angle alpha\_min.

2. Four-Bar Linkage Kinematic Analysis

This section performs a kinematic analysis of a planar four-bar linkage mechanism. The objective is to determine the output angle alpha (of link a\_4) as a function of the input angle beta (of link a\_2).

Mechanism: Defined by four link lengths (a\_1, a\_2, a\_3, a\_4).
Kinematic Equation: The relationship is governed by the implicit loop closure equation F(alpha, beta) = 0.
Methodology:

* Iterative Newton's Method: Solves the nonlinear equation F(alpha, beta) = 0 for alpha across a range of input angles beta (typically 0 degrees to 180 degrees).
* Multiple Solutions: Demonstrates how different initial guesses for Newton's method (x\_0 = 2\*pi/3 and x\_0 = -1) reveal the two distinct solution branches (configurations) inherent to the four-bar mechanism.
* Visualization: Plots alpha vs. beta to illustrate the relationship and the separate solution paths.



Note: I have included the corresponding graphic files for each code exercise in this directory.

