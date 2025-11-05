# Python Project: Dijkstra's Shortest Path Algorithm
This Python program implements Dijkstra's algorithm to efficiently determine the shortest path from a single source vertex to all other vertices in a weighted, undirected graph. This project serves as a practical demonstration of Graph Theory and Data Structures and Algorithms (DSA).

# Core Architecture
The solution uses two primary files for full functionality:

code python.py: The main script containing the complete implementation of Dijkstra's algorithm.

graph.txt: An external text file used for dynamic graph construction. The script reads this file, which defines the graph structure and edge weights in the format: vertex1 vertex2 weight.

# Key Functionalities
Optimized Algorithm: The implementation utilizes Python's built-in heapq module, which functions as a min-priority queue. This ensures the algorithm runs with optimal time complexity.


Shutterstock
Path Reconstruction: The program not only calculates the shortest distance but also accurately tracks predecessors to reconstruct and display the full sequence of vertices that form the shortest path chain.

Robust Output: The final shortest distances and corresponding paths for all vertices are presented in a clear, formatted text output.

Error Handling: The script includes checks for file existence and validation of the starting vertex.