##  Graph Representation and Adjacency Checking

This Python project implements a fundamental **Undirected Graph** data structure and demonstrates how to handle graph data stored in an external file ("graph.txt").

The project uses two classic methods to store the graph internally:

1. **Adjacency List (Dict):** An efficient structure for iterating over all neighbors of a specific vertex (used for algorithms like Breadth-First Search/Depth-First Search).
2. **Adjacency Matrix (2D List):** An efficient structure for checking if an edge exists between any two vertices (O(1) time complexity). 

### Core Functionality

1. **Input:** The graph structure (edges) is read from the **"graph.txt"** file. The file format expects one pair of connected vertices (u, v) per line, terminated by the value "-1". The vertices are numbered implicitly starting from 0 up to the largest vertex index found in the file.
2. **Display:** The program prints both the **Adjacency List** and the **Adjacency Matrix** representations to the console.
3. **Adjacency Check:** Users can interactively input two vertex indices (u and v) to instantly check if an edge exists between them using the Adjacency Matrix.

### Notes on Input Files

* **graph.txt:** The primary input file containing the graph's edge list.
* **trace.txt:** The result of the program.
