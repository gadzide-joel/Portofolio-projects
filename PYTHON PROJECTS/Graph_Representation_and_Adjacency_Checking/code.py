"""
Project Summary: Graph Representation and Adjacency Checking

This program implements an Undirected Graph data structure using a Python class called 'Graph'.
The graph is represented internally using two common structures:
1. Adjacency List (for efficient traversal, O(degree(v))).
2. Adjacency Matrix (for efficient adjacency checking, O(1)).

The script performs three main tasks:
1. Reads the graph structure (list of edges) from an external file ("graph.txt").
2. Displays the graph's structure using both the Adjacency List and Adjacency Matrix formats.
3. Allows the user to interactively check if any two given vertices are adjacent (connected by an edge).

NOTE: The program uses "graph.txt" for its primary input. It will create a dummy file if "graph.txt" is not found.
The file "trace.txt" is not used in the current version of the provided code.
"""

import numpy as np
import sys
# Used for illustration purposes:

class Graph:
    """
    Represents an undirected graph using both an Adjacency List
    (for efficient traversal) and an Adjacency Matrix (for efficient adjacency checking).
    """
    def __init__(self, order=0):
        """Initializes an empty graph with a certain number of vertices (order)"""
        self.order = order
        # Adjacency List: {vertex_index: [list_of_neighbors]}
        self.adj_list = {i: [] for i in range(order)}
        # Adjacency Matrix: [[0 or 1] * order for _ in range(order)]
        self.adj_matrix = [[0] * order for _ in range(order)]

    def add_edge(self, u, v):
        """Adds an edge between vertices u and v (undirected graph)"""
        if u not in self.adj_list or v not in self.adj_list:
            # print(f"Error: Vertices {u} or {v} out of bounds (0 to {self.order-1})")
            return False

        # Update Adjacency List (Ensures no duplicate entries for non-simple graphs)
        if v not in self.adj_list[u]:
            self.adj_list[u].append(v)
        if u not in self.adj_list[v]:
            self.adj_list[v].append(u)

        # Update Adjacency Matrix
        self.adj_matrix[u][v] = 1
        self.adj_matrix[v][u] = 1
        return True

    def display(self):
        """Displays the graph in both representations"""
        
        # --- Adjacency List Display ---
        print("\n=== Adjacency List ===")
        # Sort keys and values for clean, deterministic output
        for vertex in sorted(self.adj_list.keys()):
            print(f"{vertex}: {sorted(self.adj_list[vertex])}")

        # --- Adjacency Matrix Display ---
        print("\n=== Adjacency Matrix ===")
        # Print column indices (header)
        print("    " + " ".join(str(i) for i in range(self.order)))
        # Print matrix rows with row indices
        for i in range(self.order):
            # Format row index and join matrix row elements
            print(f"{i}: " + " ".join(str(self.adj_matrix[i][j]) for j in range(self.order)))
        # 

    def are_adjacent(self, u, v):
        """Checks if two vertices u and v are adjacent using the Adjacency Matrix"""
        if u < 0 or u >= self.order or v < 0 or v >= self.order:
            return False
        
        # Adjacency check is O(1) using the matrix
        return self.adj_matrix[u][v] == 1

def read_graph(file_name):
    """
    Reads an undirected graph from the specified file.
    The file format is expected to be pairs of vertices (u, v), one pair per line,
    terminated by -1 or EOF.
    """
    edges = []
    max_vertex = -1

    try:
        with open(file_name, 'r') as f:
            for line in f:
                line = line.strip()
                if line == "-1":
                    break
                
                # Handle empty lines or lines that can't be split correctly
                try:
                    u, v = map(int, line.split())
                except ValueError:
                    continue # Skip invalid lines

                edges.append((u, v))
                max_vertex = max(max_vertex, u, v)

    except FileNotFoundError:
        # Re-raise the exception to be caught in main()
        raise

    if max_vertex == -1:
        return None

    # The order of the graph is max_vertex + 1
    g = Graph(max_vertex + 1)
    
    # Add all edges to the graph object
    for u, v in edges:
        g.add_edge(u, v)

    return g

# --- Main Program Execution ---
def main():
    print("=== Complete Graph Manipulation Program ===")

    # Create a dummy file for demonstration if it doesn't exist
    # In a real scenario, this file should be pre-created by the user.
    file_name = "graph.txt"
    try:
        # Try to read the graph first
        g = read_graph(file_name)
    except FileNotFoundError:
        print(f"\n⚠️ WARNING: File '{file_name}' not found. Creating a dummy file for demonstration...")
        
        # Create a sample file: Vertices 0 to 7. Edges: 0-1, 0-2, 1-3, 2-4, 4-5, 6-7
        with open(file_name, 'w') as f:
            f.write("0 1\n")
            f.write("0 2\n")
            f.write("1 3\n")
            f.write("2 4\n")
            f.write("4 5\n")
            f.write("6 7\n")
            f.write("-1\n")
            
        # Read the graph from the newly created file
        try:
            g = read_graph(file_name)
        except Exception as e:
            print(f"Error reading dummy graph: {e}")
            return
            
    if not g:
        print("Error: The graph is empty.")
        return

    print(f"Successfully read graph with {g.order} vertices.")

    # 1. Full Display
    g.display()

    # 2. Adjacency Check
    print("\n--- Adjacency Check ---")
    while True:
        print("\nCheck adjacency between two vertices (enter -1 to quit).")
        try:
            a_input = input(f"Enter the first vertex (0 to {g.order - 1}): ")
            if a_input == "-1":
                break
                
            a = int(a_input)
            b = int(input(f"Enter the second vertex (0 to {g.order - 1}): "))

            if a < 0 or a >= g.order or b < 0 or b >= g.order:
                print(f" Error: Vertices must be between 0 and {g.order - 1}.")
            else:
                if g.are_adjacent(a, b):
                    print(f" The vertices {a} and {b} **are adjacent**.")
                else:
                    print(f" The vertices {a} and {b} **are not adjacent**.")

        except ValueError:
            print(" Error: Please enter valid integers.")

    print("\nProgram finished.")

if __name__ == "__main__":
    # Create an initial graph.txt file with sample data for easy testing
    # if it doesn't exist.
    main()